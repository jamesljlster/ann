#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"

int ann_config_create(ann_config_t* configPtr)
{
	struct ANN_CONFIG_STRUCT* cfgRef;
	
	cfgRef = malloc(sizeof(struct ANN_CONFIG_STRUCT));
	if(cfgRef == NULL)
	{
		return ANN_MEM_FAILED;
	}
	
	ann_config_zeromem(cfgRef);

	configPtr = cfgRef;
	
	return ANN_NO_ERROR;
}
