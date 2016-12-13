#include <stdlib.h>

#include <ann.h>
#include <ann_file_proc.h>
#include <ann_private.h>

#include "debug.h"

int ann_import(ann_t* annPtr, const char* filePath)
{
	int iResult;
	int retValue = ANN_NO_ERROR;
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

	// Parse file struct to neural network
//	iResult = ann_parse_fstruct(&annTmp, &fStruct);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

ERR:
	ann_delete(annTmp);

RET:
	ann_fstruct_delete(&fStruct);
	
	log("exit");

	return retValue;
}
