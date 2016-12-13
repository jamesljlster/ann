#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"
#include "ann_file_proc.h"
#include "ann_file_header.h"

#include "debug.h"

int ann_config_parse(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_STRUCT* fsPtr)
{
	int iResult;
	int retValue = ANN_NO_ERROR;
	
	struct ANN_CONFIG_STRUCT cfgTmp;

	struct ANN_FILE_BLOCK* fbPtr = NULL;

	// Zero memory
	ann_config_zeromem(&cfgTmp);

	// Get Topology
	fbPtr = ann_find_fblock(fsPtr, ANN_HEADER_TOPOLOGY);
	if(fbPtr == NULL)
	{
		retValue = ANN_INFO_NOT_FOUND;
		goto ERR;
	}

	
ERR:
	ann_config_delete_struct(&cfgTmp);

RET:
	return retValue;
}

