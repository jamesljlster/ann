#include <stdio.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int ann_export(ann_t ann, const char* filePath)
{
	int retValue = ANN_NO_ERROR;
	struct ANN_STRUCT* annRef = NULL;
	struct ANN_CONFIG_STRUCT* cfgRef = NULL;
	FILE* fileWrite = NULL;

	log("enter");

	// Set reference
	annRef = ann;
	cfgRef = &annRef->config;

	// Open file
	fileWrite = fopen(filePath, "w");
	if(fileWrite == NULL)
	{
		retValue = ANN_FILE_FAILED;
		goto RET;
	}

	// Write file
	ann_fprint_header(fileWrite);
	ann_fprint_config(fileWrite, cfgRef);
	ann_fprint_threshold(fileWrite, annRef);
	ann_fprint_weight(fileWrite, annRef);

RET:
	if(fileWrite != NULL)
		fclose(fileWrite);
	log("exit");
	return retValue;
}

int ann_config_export(ann_config_t config, const char* filePath)
{
	int retValue = ANN_NO_ERROR;
	struct ANN_CONFIG_STRUCT* cfgRef = NULL;
	FILE* fileWrite = NULL;

	log("enter");

	// Set reference
	cfgRef = config;

	// Open file
	fileWrite = fopen(filePath, "w");
	if(fileWrite == NULL)
	{
		retValue = ANN_FILE_FAILED;
		goto RET;
	}

	// Write file
	ann_fprint_config(fileWrite, cfgRef);

RET:
	if(fileWrite != NULL)
		fclose(fileWrite);
	log("exit");
	return retValue;
}

