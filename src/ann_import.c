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

	log("enter");

	// Zero memory
	ann_fstruct_zeromem(&fStruct);

	// Create file struct
	iResult = ann_fstruct_create(&fStruct, filePath);
	if(iResult != ANN_NO_ERROR)
	{
		log("ann_fstruct_create() failed");
		retValue = iResult;
		goto RET;
	}

	// Memory allocation
	annRef = malloc(sizeof(struct ANN_STRUCT));
	if(annRef == NULL)
	{
		log("malloc() failed");
		retValue = ANN_MEM_FAILED;
		goto RET;
	}
	else
	{
		ann_zeromem(annRef);
		cfgRef = &annRef->config;
	}

	// Parse config
	iResult = ann_parse_config(cfgRef, &fStruct);
	if(iResult != ANN_NO_ERROR)
	{
		log("ann_parse_config() failed");
		retValue = iResult;
		goto ERR;
	}

	// Parse network
	iResult = ann_parse_network(annRef, &fStruct);
	if(iResult != ANN_NO_ERROR)
	{
		log("ann_parse_network() failed");
		retValue = iResult;
		goto ERR;
	}

	// Assign value
	*annPtr = annRef;

	goto RET;

ERR:
	ann_delete((ann_t)annRef);

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
	struct ANN_CONFIG_STRUCT* cfgRef = NULL;

	log("enter");

	// Zero memory
	ann_fstruct_zeromem(&fStruct);
	
	// Create file struct
	iResult = ann_fstruct_create(&fStruct, filePath);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Memory allocation
	cfgRef = malloc(sizeof(struct ANN_CONFIG_STRUCT));
	if(cfgRef == NULL)
	{
		retValue = ANN_NO_ERROR;
		goto RET;
	}
	else
	{
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
	*configPtr = cfgRef;

	goto RET;

ERR:
	if(cfgRef != NULL)
		free(cfgRef);

RET:
	ann_fstruct_delete(&fStruct);
	log("exit");
	return retValue;
}

