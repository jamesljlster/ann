#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int ann_config_create(ann_config_t* configPtr)
{
	struct ANN_CONFIG_STRUCT* cfgRef;
	
	cfgRef = malloc(sizeof(struct ANN_CONFIG_STRUCT));
	if(cfgRef == NULL)
	{
		return ANN_MEM_FAILED;
	}
	
	ann_config_zeromem(cfgRef);

	*configPtr = cfgRef;
	
	return ANN_NO_ERROR;
}

int ann_create(ann_t* annPtr, ann_config_t config)
{
	int iResult;
	int retValue = ANN_NO_ERROR;
	struct ANN_STRUCT* annRef = NULL;
	struct ANN_CONFIG_STRUCT* cfgRef = config;
	
	log("enter");

	// Memory allocation
	annRef = malloc(sizeof(struct ANN_STRUCT));
	if(annRef == NULL)
	{
		return ANN_MEM_FAILED;
	}
	else
	{
		ann_zeromem(annRef);
	}

	// Clone config
	iResult = ann_clone_config(&annRef->config, cfgRef);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Create nerwork
	iResult = ann_allocate_network(annRef);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Assign value
	*annPtr = annRef;

	goto RET;

ERR:
	ann_delete_struct(annRef);

RET:
	log("exit");
	return retValue;
}
