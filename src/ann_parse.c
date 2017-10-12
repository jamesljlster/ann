#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ann.h"
#include "ann_private.h"
#include "ann_file_proc.h"
#include "ann_file_header.h"
#include "ann_builtin_math.h"

#include "debug.h"

int ann_parse_config_tfunc(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr);
int ann_parse_config_topology(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr);
int ann_parse_config_training_info(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr);
int ann_parse_config_total_node(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr);
int ann_parse_threshold(struct ANN_STRUCT* asPtr, struct ANN_FILE_BLOCK* fbPtr);
int ann_parse_weight(struct ANN_STRUCT* asPtr, struct ANN_FILE_BLOCK* fbPtr);
int ann_parse_recurrent_weight(struct ANN_STRUCT* asPtr, struct ANN_FILE_BLOCK* fbPtr);

int ann_parse_network(struct ANN_STRUCT* asPtr, struct ANN_FILE_STRUCT* fsPtr, int type)
{
	int iResult;
	int retValue = ANN_NO_ERROR;
	struct ANN_FILE_BLOCK* fbPtr = NULL;

	LOG("enter");

	// Checking
	assert(asPtr->layerList == NULL);
	assert(asPtr->config.inputs > 0);
	assert(asPtr->config.outputs > 0);
	assert(asPtr->config.layers >= 2);
	//assert(asPtr->config.tFuncList != NULL);
	assert(asPtr->config.nodeList != NULL);

	// Allocate network
	iResult = ann_allocate_network(asPtr);
	if(iResult != ANN_NO_ERROR)
	{
		LOG("ann_allocate_network() failed");
		retValue = iResult;
		goto RET;
	}

	// Get threshold
	fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_THRESHOLD_VALUE);
	if(fbPtr == NULL)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	// Parse threshold
	iResult = ann_parse_threshold(asPtr, fbPtr);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Get weight
	fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_WEIGHT_FACTOR);
	if(fbPtr == NULL)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	// Parse weight
	iResult = ann_parse_weight(asPtr, fbPtr);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// For recurrent neural network
	if(type == ANN_NETWORK_RNN)
	{
		// Get recurrent weight
		fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_RECURRENT_WEIGHT);
		if(fbPtr == NULL)
		{
			retValue = ANN_INFO_NOT_FOUND;
			goto RET;
		}

		// Parse recurrent weight
		iResult = ann_parse_recurrent_weight(asPtr, fbPtr);
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}
	}

RET:
	LOG("exit");
	return retValue;
}

int ann_parse_threshold(struct ANN_STRUCT* asPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int retValue = ANN_NO_ERROR;

	int layerIndex;
	int nodeIndex;
	double tmpValue;

	char** strList = NULL;
	int strCount = 0;

	char** childStrList = NULL;
	int childStrCount = 0;

	char* tmpPtr = NULL;

	LOG("enter");

	// Checking
	iResult = ann_strcmp(fbPtr->header, ann_file_header[ANN_HEADER_THRESHOLD_VALUE]);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	for(i = 1; i < fbPtr->strCount; i++)
	{
		// Extract string
		iResult = ann_str_extract(&strList, &strCount, fbPtr->strList[i], '=');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(strCount != 2)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Extract child string
		iResult = ann_str_extract(&childStrList, &childStrCount, strList[0], '-');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(childStrCount != 2)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Parsing
		layerIndex = strtol(childStrList[0], &tmpPtr, 10);
		if(tmpPtr == childStrList[0])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		nodeIndex = strtol(childStrList[1], &tmpPtr, 10);
		if(tmpPtr == childStrList[1])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		tmpValue = strtod(strList[1], &tmpPtr);
		if(tmpPtr == strList[1])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Set threshold
		iResult = ann_set_threshold_struct(asPtr, layerIndex - 1, nodeIndex - 1, tmpValue);
		if(iResult != ANN_NO_ERROR)
		{
			LOG("set threshold failed with:");
			LOG("Origin string: %s", fbPtr->strList[i]);
			LOG("strList = {%s, %s}", strList[0], strList[1]);
			LOG("childStrList = {%s, %s}", childStrList[0], childStrList[1]);
			LOG("childStrList[1][0] in int = %d", childStrList[1][0]);
			LOG("childStrList[1][1] in int = %d", childStrList[1][1]);
			LOG("childStrList[1][2] in int = %d", childStrList[1][2]);
			LOG("Decode info: layerIndex = %d, nodeIndex = %d, threshold = %lf", layerIndex, nodeIndex, tmpValue);
			retValue = iResult;
			goto RET;
		}

		// Cleanup
		for(j = 0; j < strCount; j++)
		{
			free(strList[j]);
		}
		free(strList);
		strList = NULL;

		for(j = 0; j < childStrCount; j++)
		{
			free(childStrList[j]);
		}
		free(childStrList);
		childStrList = NULL;
	}

RET:
	if(strList != NULL)
	{
		for(i = 0; i < strCount; i++)
		{
			if(strList[i] != NULL)
				free(strList[i]);
		}
		free(strList);
	}

	if(childStrList != NULL)
	{
		for(i = 0; i < childStrCount; i++)
		{
			if(childStrList[i] != NULL)
				free(childStrList[i]);
		}
		free(childStrList);
	}

	LOG("exit");
	return retValue;
}

int ann_parse_recurrent_weight(struct ANN_STRUCT* asPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int retValue = ANN_NO_ERROR;

	int preNodeIndex;
	int nodeIndex;
	double tmpValue;

	char** strList = NULL;
	int strCount = 0;

	char** childStrList = NULL;
	int childStrCount = 0;

	char* tmpPtr = NULL;

	LOG("enter");

	// Checking
	iResult = ann_strcmp(fbPtr->header, ann_file_header[ANN_HEADER_RECURRENT_WEIGHT]);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	for(i = 1; i < fbPtr->strCount; i++)
	{
		// Extract string
		iResult = ann_str_extract(&strList, &strCount, fbPtr->strList[i], '=');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(strCount != 2)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Extract child string
		iResult = ann_str_extract(&childStrList, &childStrCount, strList[0], '-');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(childStrCount != 2)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Parsing
		preNodeIndex = strtol(childStrList[0], &tmpPtr, 10);
		if(tmpPtr == childStrList[0])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		nodeIndex = strtol(childStrList[1], &tmpPtr, 10);
		if(tmpPtr == childStrList[1])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		tmpValue = strtod(strList[1], &tmpPtr);
		if(tmpPtr == strList[1])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Set weight
		iResult = ann_set_recurrent_weight_struct(asPtr, preNodeIndex - 1, nodeIndex - 1, tmpValue);
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Cleanup
		for(j = 0; j < strCount; j++)
		{
			free(strList[j]);
		}
		free(strList);
		strList = NULL;

		for(j = 0; j < childStrCount; j++)
		{
			free(childStrList[j]);
		}
		free(childStrList);
		childStrList = NULL;
	}

RET:
	if(strList != NULL)
	{
		for(i = 0; i < strCount; i++)
		{
			if(strList[i] != NULL)
				free(strList[i]);
		}
		free(strList);
	}

	if(childStrList != NULL)
	{
		for(i = 0; i < childStrCount; i++)
		{
			if(childStrList[i] != NULL)
				free(childStrList[i]);
		}
		free(childStrList);
	}

	LOG("exit");
	return retValue;
}

int ann_parse_weight(struct ANN_STRUCT* asPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int retValue = ANN_NO_ERROR;

	int layerIndex;
	int preNodeIndex;
	int nodeIndex;
	double tmpValue;

	char** strList = NULL;
	int strCount = 0;

	char** childStrList = NULL;
	int childStrCount = 0;

	char* tmpPtr = NULL;

	LOG("enter");

	// Checking
	iResult = ann_strcmp(fbPtr->header, ann_file_header[ANN_HEADER_WEIGHT_FACTOR]);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	for(i = 1; i < fbPtr->strCount; i++)
	{
		// Extract string
		iResult = ann_str_extract(&strList, &strCount, fbPtr->strList[i], '=');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(strCount != 2)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Extract child string
		iResult = ann_str_extract(&childStrList, &childStrCount, strList[0], '-');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(childStrCount != 3)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Parsing
		layerIndex = strtol(childStrList[0], &tmpPtr, 10);
		if(tmpPtr == childStrList[0])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		preNodeIndex = strtol(childStrList[1], &tmpPtr, 10);
		if(tmpPtr == childStrList[1])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		nodeIndex = strtol(childStrList[2], &tmpPtr, 10);
		if(tmpPtr == childStrList[2])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		tmpValue = strtod(strList[1], &tmpPtr);
		if(tmpPtr == strList[1])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Set weight
		iResult = ann_set_weight_struct(asPtr, layerIndex - 1, preNodeIndex - 1, nodeIndex - 1, tmpValue);
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Cleanup
		for(j = 0; j < strCount; j++)
		{
			free(strList[j]);
		}
		free(strList);
		strList = NULL;

		for(j = 0; j < childStrCount; j++)
		{
			free(childStrList[j]);
		}
		free(childStrList);
		childStrList = NULL;
	}

RET:
	if(strList != NULL)
	{
		for(i = 0; i < strCount; i++)
		{
			if(strList[i] != NULL)
				free(strList[i]);
		}
		free(strList);
	}

	if(childStrList != NULL)
	{
		for(i = 0; i < childStrCount; i++)
		{
			if(childStrList[i] != NULL)
				free(childStrList[i]);
		}
		free(childStrList);
	}

	LOG("exit");
	return retValue;
}

int ann_parse_config(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_STRUCT* fsPtr)
{
	int iResult;
	int retValue = ANN_NO_ERROR;

	struct ANN_CONFIG_STRUCT cfgTmp;

	struct ANN_FILE_BLOCK* fbPtr = NULL;

	LOG("enter");

	// Zero memory
	ann_config_zeromem(&cfgTmp);

	// Get Topology
	fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_TOPOLOGY);
	if(fbPtr == NULL)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}
	else
	{
		// Checking
		if(fbPtr->strCount < ANN_HEADER_TOPOLOGY_LIST_COUNT)
		{
			retValue = ANN_INFO_NOT_FOUND;
			goto RET;
		}
	}

	// Parse Topology
	iResult = ann_parse_config_topology(&cfgTmp, fbPtr);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Check transfer function
	if(cfgTmp.tFuncRoot == ANN_TFUNC_MULTIPLE)
	{
		// Get Transfer function
		fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_TFUNC);
		if(fbPtr == NULL)
		{
			retValue = ANN_INFO_NOT_FOUND;
			goto RET;
		}

		// Parse Transfer function
		iResult = ann_parse_config_tfunc(&cfgTmp, fbPtr);
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}
	}

	// Get Training info
	fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_TRAINING_INFO);
	if(fbPtr == NULL)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}
	else
	{
		// Checking
		if(fbPtr->strCount < ANN_HEADER_TRAINING_INFO_LIST_COUNT)
		{
			retValue = ANN_INFO_NOT_FOUND;
			goto RET;
		}
	}

	// Parse Training info
	iResult = ann_parse_config_training_info(&cfgTmp, fbPtr);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Get Total node
	fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_TOTAL_NODE);
	if(fbPtr == NULL)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	// Parse Total node
	iResult = ann_parse_config_total_node(&cfgTmp, fbPtr);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Assign values
	ann_clone_config_struct(cfgPtr, &cfgTmp);

RET:
	ann_config_delete_struct(&cfgTmp);
	LOG("exit");
	return retValue;
}

int ann_parse_config_tfunc(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int retValue = ANN_NO_ERROR;

	int tmpIndex;
	int tmpValue;

	int* tFuncList = NULL;
	void* allocTmp = NULL;

	char** strList = NULL;
	int strCount = 0;

	char* tmpPtr = NULL;

	LOG("enter");

	// Checking
	if(cfgPtr->layers <= 0)
	{
		retValue = ANN_INVALID_ARG;
		goto RET;
	}

	iResult = ann_strcmp(fbPtr->header, ann_file_header[ANN_HEADER_TFUNC]);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	tFuncList = calloc(cfgPtr->layers, sizeof(int));
	if(tFuncList == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto RET;
	}

	for(i = 1; i < fbPtr->strCount; i++)
	{
		// Extract string
		iResult = ann_str_extract(&strList, &strCount, fbPtr->strList[i], '=');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(strCount != 2)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Parsing
		tmpIndex = strtol(strList[0], &tmpPtr, 10);
		if(tmpPtr == strList[0])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		tmpValue = ann_get_transfer_func_id(strList[1]);
		if(tmpValue < 0)
		{
			retValue = tmpValue;
			goto RET;
		}

		// Set transfer function
		tFuncList[tmpIndex - 1] = tmpValue;

		// Cleanup
		for(j = 0; j < strCount; j++)
		{
			free(strList[j]);
		}
		free(strList);
		strList = NULL;
	}

	// Assign values
	cfgPtr->tFuncList = tFuncList;

	tFuncList = NULL;

RET:
	if(allocTmp != NULL)
		free(allocTmp);

	if(tFuncList != NULL)
		free(tFuncList);

	if(strList != NULL)
	{
		for(i = 0; i < strCount; i++)
		{
			if(strList[i] != NULL)
				free(strList[i]);
		}
		free(strList);
	}

	LOG("exit");
	return retValue;
}

int ann_parse_config_total_node(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int retValue = ANN_NO_ERROR;

	int tmpIndex;
	int tmpValue;

	int* nodeList = NULL;
	void* allocTmp = NULL;

	char** strList = NULL;
	int strCount = 0;

	char* tmpPtr = NULL;

	LOG("enter");

	// Checking
	if(cfgPtr->layers <= 0)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	iResult = ann_strcmp(fbPtr->header, ann_file_header[ANN_HEADER_TOTAL_NODE]);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	nodeList = calloc(cfgPtr->layers, sizeof(int));
	if(nodeList == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto RET;
	}

	for(i = 1; i < fbPtr->strCount; i++)
	{
		// Extract string
		iResult = ann_str_extract(&strList, &strCount, fbPtr->strList[i], '=');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(strCount != 2)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Parsing
		tmpIndex = strtol(strList[0], &tmpPtr, 10);
		if(tmpPtr == strList[0])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		tmpValue = strtol(strList[1], &tmpPtr, 10);
		if(tmpPtr == strList[1])
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Set node
		nodeList[tmpIndex - 1] = tmpValue;

		// Cleanup
		for(j = 0; j < strCount; j++)
		{
			free(strList[j]);
		}
		free(strList);
		strList = NULL;
	}

	nodeList[0] = cfgPtr->inputs;
	nodeList[cfgPtr->layers - 1] = cfgPtr->outputs;

	// Checking
	for(i = 0; i < cfgPtr->layers; i++)
	{
		if(nodeList[i] <= 0)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}
	}

	// Assign values
	cfgPtr->nodeList = nodeList;

	nodeList = NULL;

RET:
	if(allocTmp != NULL)
		free(allocTmp);

	if(nodeList != NULL)
		free(nodeList);

	if(strList != NULL)
	{
		for(i = 0; i < strCount; i++)
		{
			if(strList[i] != NULL)
				free(strList[i]);
		}
		free(strList);
	}

	LOG("exit");
	return retValue;
}

int ann_parse_config_training_info(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int strID;
	int retValue = ANN_NO_ERROR;

	double tmpValue;

	char** strList = NULL;
	int strCount = 0;

	char* tmpPtr = NULL;

	LOG("enter");

	// Checking
	iResult = ann_strcmp(fbPtr->header, ann_file_header[ANN_HEADER_TRAINING_INFO]);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	for(i = 0; i < fbPtr->strCount; i++)
	{
		// Extract string
		iResult = ann_str_extract(&strList, &strCount, fbPtr->strList[i], '=');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(strCount != 2)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Parsing
		strID = ann_get_training_content_id(strList[0]);
		if(strID < 0)
		{
			retValue = strID;
			goto RET;
		}

		switch(strID)
		{
			case ANN_HEADER_TRAINING_INFO_LEARNING_RATE:
				tmpValue = strtod(strList[1], &tmpPtr);
				if(tmpPtr == strList[1])
				{
					retValue = ANN_SYNTAX_ERROR;
					goto RET;
				}
				else
				{
					cfgPtr->learningRate = tmpValue;
				}
				break;

			case ANN_HEADER_TRAINING_INFO_MOMENTUM_COEF:
				tmpValue = strtod(strList[1], &tmpPtr);
				if(tmpPtr == strList[1])
				{
					retValue = ANN_SYNTAX_ERROR;
					goto RET;
				}
				else
				{
					cfgPtr->momentumCoef = tmpValue;
				}
				break;

			default:
				retValue = ANN_SYNTAX_ERROR;
				goto RET;
		}

		// Cleanup
		for(j = 0; j < strCount; j++)
		{
			free(strList[j]);
		}
		free(strList);
		strList = NULL;
	}

RET:
	if(strList != NULL)
	{
		for(i = 0; i < strCount; i++)
		{
			if(strList[i] != NULL)
				free(strList[i]);
		}
		free(strList);
	}

	LOG("exit");
	return retValue;
}

int ann_parse_config_topology(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int strID;
	int tmpValue;
	int retValue = ANN_NO_ERROR;

	char** strList = NULL;
	int strCount = 0;

	char* tmpPtr = NULL;

	LOG("enter");

	// Checking
	iResult = ann_strcmp(fbPtr->header, ann_file_header[ANN_HEADER_TOPOLOGY]);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	for(i = 0; i < fbPtr->strCount; i++)
	{
		// Extract string
		iResult = ann_str_extract(&strList, &strCount, fbPtr->strList[i], '=');
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		// Checking
		if(strCount != 2)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Parsing
		strID = ann_get_topology_content_id(strList[0]);
		if(strID < 0)
		{
			LOG("Get topology content id with %s failed!", strList[0]);
			retValue = strID;
			goto RET;
		}

		switch(strID)
		{
			case ANN_HEADER_TOPOLOGY_INPUTS:
				tmpValue = strtol(strList[1], &tmpPtr, 10);
				if(tmpPtr == strList[1])
				{
					retValue = ANN_SYNTAX_ERROR;
					goto RET;
				}
				else
				{
					cfgPtr->inputs = tmpValue;
				}
				break;

			case ANN_HEADER_TOPOLOGY_OUTPUTS:
				tmpValue = strtol(strList[1], &tmpPtr, 10);
				if(tmpPtr == strList[1])
				{
					retValue = ANN_SYNTAX_ERROR;
					goto RET;
				}
				else
				{
					cfgPtr->outputs = tmpValue;
				}
				break;

			case ANN_HEADER_TOPOLOGY_LAYERS:
				tmpValue = strtol(strList[1], &tmpPtr, 10);
				if(tmpPtr == strList[1])
				{
					retValue = ANN_SYNTAX_ERROR;
					goto RET;
				}
				else
				{
					cfgPtr->layers = tmpValue;
				}
				break;

			case ANN_HEADER_TOPOLOGY_TRANSFER_FUNC:
				tmpValue = ann_get_transfer_func_id(strList[1]);
				if(tmpValue < 0)
				{
					retValue = tmpValue;
					goto RET;
				}
				else
				{
					cfgPtr->tFuncRoot = tmpValue;
				}
				break;

			default:
				LOG("Invalid ID: %d", strID);
				retValue = ANN_SYNTAX_ERROR;
				goto RET;
		}

		// Cleanup
		for(j = 0; j < strCount; j++)
		{
			free(strList[j]);
		}
		free(strList);
		strList = NULL;
	}

RET:
	if(strList != NULL)
	{
		for(i = 0; i < strCount; i++)
		{
			if(strList[i] != NULL)
				free(strList[i]);
		}
		free(strList);
	}

	LOG("exit");
	return retValue;
}

