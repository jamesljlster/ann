#include <stdlib.h>
#include <errno.h>

#include "ann.h"
#include "ann_private.h"
#include "ann_file_proc.h"
#include "ann_file_header.h"

#include "debug.h"

int ann_config_parse_topology(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr);
int ann_config_parse_training_info(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr);
int ann_config_parse_total_node(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr);

int ann_config_parse(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_STRUCT* fsPtr)
{
	int i;
	int iResult;
	int retValue = ANN_NO_ERROR;
	
	struct ANN_CONFIG_STRUCT cfgTmp;

	struct ANN_FILE_BLOCK* fbPtr = NULL;
	
	log("enter");

	// Zero memory
	ann_config_zeromem(&cfgTmp);

	// Get Topology
	fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_TOPOLOGY);
	if(fbPtr == NULL)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto ERR;
	}
	else
	{
		// Checking
		if(fbPtr->strCount < ANN_HEADER_TOPOLOGY_LIST_COUNT)
		{
			retValue = ANN_INFO_NOT_FOUND;
			goto ERR;
		}
	}
	
	// Parse Topology
	iResult = ann_config_parse_topology(&cfgTmp, fbPtr);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Get Training info
	fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_TRAINING_INFO);
	if(fbPtr == NULL)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto ERR;
	}
	else
	{
		// Checking
		if(fbPtr->strCount < ANN_HEADER_TRAINING_INFO_LIST_COUNT)
		{
			retValue = ANN_INFO_NOT_FOUND;
			goto ERR;
		}
	}

	// Parse Training info
	iResult = ann_config_parse_training_info(&cfgTmp, fbPtr);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Get Total node
	fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_TOTAL_NODE);
	if(fbPtr == NULL)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto ERR;
	}

	// Parse Total node
	iResult = ann_config_parse_total_node(&cfgTmp, fbPtr);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = ANN_NO_ERROR;
		goto ERR;
	}

	// Assign values
	*cfgPtr = cfgTmp;

	goto RET;

ERR:
	ann_config_delete_struct(&cfgTmp);

RET:
	log("exit");
	return retValue;
}

int ann_config_parse_total_node(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int strID;
	int retValue = ANN_NO_ERROR;
	
	int tmpIndex;
	int tmpValue;

	int* nodeList = NULL;
	void* allocTmp = NULL;

	char** strList = NULL;
	int strCount = 0;
	
	log("enter");

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
		tmpIndex = strtol(strList[0], NULL, 0);
		if(errno == ERANGE)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		tmpValue = strtol(strList[1], NULL, 0);
		if(errno == ERANGE)
		{
			retValue = ANN_SYNTAX_ERROR;
			goto RET;
		}

		// Set node
		nodeList[i] = tmpValue;
		
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
	
	log("exit");
	return retValue;
}

int ann_config_parse_training_info(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int strID;
	int retValue = ANN_NO_ERROR;
	
	double tmpValue;

	char** strList = NULL;
	int strCount = 0;
	
	log("enter");

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
				tmpValue = strtod(strList[1], NULL);
				if(errno == ERANGE)
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
				tmpValue = strtod(strList[1], NULL);
				if(errno == ERANGE)
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
	
	log("exit");
	return retValue;
}

int ann_config_parse_topology(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_BLOCK* fbPtr)
{
	int i, j;
	int iResult;
	int strID;
	int tmpValue;
	int retValue = ANN_NO_ERROR;
	
	char** strList = NULL;
	int strCount = 0;
	
	log("enter");

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
			log("Get topology content id with %s failed!", strList[0]);
			retValue = strID;
			goto RET;
		}

		switch(strID)
		{
			case ANN_HEADER_TOPOLOGY_INPUTS:
				tmpValue = strtol(strList[1], NULL, 0);
				if(errno == ERANGE)
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
				tmpValue = strtol(strList[1], NULL, 0);
				if(errno == ERANGE)
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
				tmpValue = strtol(strList[1], NULL, 0);
				if(errno == ERANGE)
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
					cfgPtr->transferFuncIndex = tmpValue;
				}
				break;

			default:
				log("Invalid ID: %d", strID);
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
	
	log("exit");
	return retValue;
}

