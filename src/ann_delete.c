#include <stdlib.h>

#include <ann.h>
#include <ann_private.h>

#include "debug.h"

void ann_config_delete(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgPtr = config;
	
	log("enter");

	if(config != NULL)
	{
		ann_delete_config_struct(cfgPtr);
		free(config);
	}

	log("exit");
}

void ann_delete_config_struct(struct ANN_CONFIG_STRUCT* cfgPtr)
{
	log("enter");

	if(cfgPtr->nodeList != NULL)
		free(cfgPtr->nodeList);

	log("exit");
}

void ann_delete_node(struct ANN_NODE* nodePtr)
{
	int i;
	
	log("enter");

	if(nodePtr->weight != NULL)
	{
		free(nodePtr->weight);
	}

	log("exit");
}

void ann_delete_layer(struct ANN_LAYER* layerPtr)
{
	int i;

	log("enter");

	if(layerPtr->nodeList != NULL)
	{
		for(i = 0; i < layerPtr->nodeCount; i++)
		{
			ann_delete_node(&layerPtr->nodeList[i]);
		}
		free(layerPtr->nodeList);
	}

	log("exit");
}

void ann_delete_struct(struct ANN_STRUCT* structPtr)
{
	int i;

	log("enter");

	if(structPtr->layerList != NULL)
	{
		for(i = 0; i < structPtr->config.layers; i++)
		{
			ann_delete_layer(&structPtr->layerList[i]);
		}
		free(structPtr->layerList);
	}
	
	ann_delete_config_struct(&structPtr->config);

	log("exit");
}

void ann_delete(ann_t ann)
{
	struct ANN_STRUCT* annRef = ann;
	
	log("enter");

	if(annRef != NULL)
	{
		ann_delete_struct(annRef);
		free(annRef);
	}

	log("exit");
}

