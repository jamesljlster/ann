#include <stdlib.h>

#include <ann.h>
#include <ann_file_proc.h>
#include <ann_private.h>

#include "debug.h"

int ann_import(ann_t* annPtr, const char* filePath)
{
	int iResult;
	int retValue = ANN_NO_ERROR;

	struct ANN_STRUCT* annRef;
	struct ANN_CONFIG_STRUCT* cfgRef;
	struct ANN_FILE_STRUCT fStruct;

	ann_t annTmp = NULL;

	log("enter");

	// Zero memory
	ann_fstruct_zeromem(&fStruct);

	// Create file struct
	iResult = ann_fstruct_create(&fStruct, filePath);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Memory allocation
	annTmp = malloc(sizeof(struct ANN_STRUCT));
	if(annTmp == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto RET;
	}
	else
	{
		annRef = annTmp;
		cfgRef = &annRef->config;
		ann_zeromem(annRef);
	}

	// Parse config
	iResult = ann_parse_config(cfgRef, &fStruct);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Parse network
	iResult = ann_parse_network(annRef, &fStruct);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Assign value
	*annPtr = annTmp;

	goto RET;

ERR:
	ann_delete(annTmp);

RET:
	ann_fstruct_delete(&fStruct);
	
	log("exit");

	return retValue;
}

int ann_config_import(ann_config_t* configPtr, const char* filePath)
{
	int iResult;
	int retValue = ANN_NO_ERROR;
	
	struct ANN_FILE_STRUCT fStruct;
	struct ANN_CONFIG_STRUCT* cfgRef;

	ann_config_t cfgTmp = NULL;

	log("enter");
	
	// Create file struct
	iResult = ann_fstruct_create(&fStruct, filePath);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Memory allocation
	cfgTmp = malloc(sizeof(struct ANN_CONFIG_STRUCT));
	if(cfgTmp == NULL)
	{
		retValue = ANN_NO_ERROR;
		goto RET;
	}
	else
	{
		cfgRef = cfgTmp;
		ann_config_zeromem(cfgRef);
	}

	// Parsing
	iResult = ann_parse_config(cfgRef, &fStruct);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Assign value
	*configPtr = cfgTmp;

ERR:
	if(cfgTmp != NULL)
		free(cfgTmp);

RET:
	ann_fstruct_delete(&fStruct);
	log("exit");
	return retValue;
}

