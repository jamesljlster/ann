#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

void ann_config_delete(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgPtr = config;
	
	LOG("enter");

	if(config != NULL)
	{
		ann_config_delete_struct(cfgPtr);
		free(config);
	}

	LOG("exit");
}

void ann_config_delete_struct(struct ANN_CONFIG_STRUCT* cfgPtr)
{
	LOG("enter");

	if(cfgPtr->nodeList != NULL)
	{
		free(cfgPtr->nodeList);
		cfgPtr->nodeList = NULL;
	}

	LOG("exit");
}

void ann_delete_node(struct ANN_NODE* nodePtr)
{
	LOG("enter");

	if(nodePtr->weight != NULL)
	{
		free(nodePtr->weight);
		nodePtr->weight = NULL;
	}
	
	if(nodePtr->deltaW != NULL)
	{
		free(nodePtr->deltaW);
		nodePtr->deltaW = NULL;
	}

	LOG("exit");
}

void ann_delete_layer(struct ANN_LAYER* layerPtr)
{
	int i;

	LOG("enter");

	if(layerPtr->nodeList != NULL)
	{
		for(i = 0; i < layerPtr->nodeCount; i++)
		{
			ann_delete_node(&layerPtr->nodeList[i]);
		}
		free(layerPtr->nodeList);
		layerPtr->nodeList = NULL;
	}

	LOG("exit");
}

void ann_delete_struct(struct ANN_STRUCT* structPtr)
{
	int i;

	LOG("enter");

	if(structPtr->layerList != NULL)
	{
		for(i = 0; i < structPtr->config.layers; i++)
		{
			ann_delete_layer(&structPtr->layerList[i]);
		}
		free(structPtr->layerList);
		structPtr->layerList = NULL;
	}
	
	ann_config_delete_struct(&structPtr->config);

	LOG("exit");
}

void ann_delete(ann_t ann)
{
	struct ANN_STRUCT* annRef = ann;
	
	LOG("enter");

	if(annRef != NULL)
	{
		ann_delete_struct(annRef);
		free(annRef);
	}

	LOG("exit");
}

