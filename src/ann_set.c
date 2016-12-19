#include <stdlib.h>
#include <assert.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

#define INIT_NODES	10

int ann_config_set_inputs(ann_config_t config, int inputs)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;
	
	cfgRef->inputs = inputs;

	return ANN_NO_ERROR;
}

int ann_config_set_outputs(ann_config_t config, int outputs)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;
	
	cfgRef->outputs = outputs;

	return ANN_NO_ERROR;
}

int ann_config_set_layers(ann_config_t config, int hiddenLayers)
{
	int i;
	int retValue = ANN_NO_ERROR;
	int tmpLayerCount;
	int preLayerCount;
	int* tmpList = NULL;

	struct ANN_CONFIG_STRUCT* cfgRef = config;
	
	log("enter");

	tmpLayerCount = hiddenLayers + 2;
	
	// Memory allocation
	tmpList = calloc(tmpLayerCount, sizeof(int));
	if(tmpList == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto RET;
	}
	else
	{
		tmpList[0] = cfgRef->inputs;
		tmpList[tmpLayerCount - 1] = cfgRef->outputs;

		for(i = 1; i < tmpLayerCount - 1; i++)
			tmpList[i] = INIT_NODES;
	}

	if(cfgRef->nodeList != NULL)
	{
		preLayerCount = cfgRef->layers;

		for(i = 1; i < preLayerCount - 1; i++)
			tmpList[i] = cfgRef->nodeList[i];
		
		free(cfgRef->nodeList);
	}

	// Assign values
	cfgRef->nodeList = tmpList;
	cfgRef->layers = tmpLayerCount;

RET:
	log("exit");
	return ANN_NO_ERROR;
}

int ann_config_set_nodes(ann_config_t config, int hiddenLayerIndex, int nodes)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	// Checking
	if(hiddenLayerIndex <= 1 || hiddenLayerIndex >= cfgRef->layers - 1)
		return ANN_OUT_OF_RANGE;

	cfgRef->nodeList[hiddenLayerIndex + 1] = nodes;

	return ANN_NO_ERROR;
}

int ann_config_set_transfer_func(ann_config_t config, int tFuncIndex)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;
	
	cfgRef->transferFuncIndex = tFuncIndex;

	return ANN_NO_ERROR;
}

int ann_set_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex, double value)
{
	struct ANN_STRUCT* annRef = ann;
	return ann_set_weight_struct(annRef, layerIndex, preNodeIndex, nodeIndex, value);
}

int ann_set_threshold(ann_t ann, int layerIndex, int nodeIndex, double value)
{
	struct ANN_STRUCT* annRef = ann;
	return ann_set_threshold_struct(annRef, layerIndex, nodeIndex, value);
}

int ann_set_weight_struct(struct ANN_STRUCT* sptr, int layerIndex, int preNodeIndex, int nodeIndex, double value)
{
	struct ANN_LAYER* preLayerRef;
	struct ANN_LAYER* layerRef;
	struct ANN_NODE* nodeRef;

	// Checking
	assert(sptr->layerList != NULL);

	if(layerIndex >= sptr->config.layers || layerIndex <= 0)
		return ANN_OUT_OF_RANGE;
	
	preLayerRef = &sptr->layerList[layerIndex - 1];
	layerRef = &sptr->layerList[layerIndex];

	if(preNodeIndex < 0 || preNodeIndex >= preLayerRef->nodeCount)
		return ANN_OUT_OF_RANGE;
	if(nodeIndex < 0 || nodeIndex >= layerRef->nodeCount)
		return ANN_OUT_OF_RANGE;

	layerRef->nodeList[nodeIndex].weight[preNodeIndex] = value;

	return ANN_NO_ERROR;
}

int ann_set_threshold_struct(struct ANN_STRUCT* sptr, int layerIndex, int nodeIndex, double value)
{
	struct ANN_LAYER* layerRef;
	struct ANN_NODE* nodeRef;

	// Checking
	assert(sptr->layerList != NULL);
	
	if(layerIndex >= sptr->config.layers || layerIndex < 0)
		return ANN_OUT_OF_RANGE;
	
	layerRef = &sptr->layerList[layerIndex];

	if(nodeIndex < 0 || nodeIndex >= layerRef->nodeCount)
		return ANN_OUT_OF_RANGE;

	layerRef->nodeList[nodeIndex].threshold = value;

	return ANN_NO_ERROR;
}

