#include <assert.h>

#include "ann.h"
#include "ann_private.h"

ann_config_t ann_get_config(ann_t ann)
{
	struct ANN_STRUCT* annRef = ann;

	return &annRef->config;
}

int ann_config_get_inputs(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	return cfgRef->inputs;
}

int ann_config_get_outputs(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	return cfgRef->outputs;
}

int ann_config_get_hidden_layers(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	return cfgRef->layers - 2;
}

int ann_config_get_nodes(ann_config_t config, int hiddenLayerIndex)
{
	int layerIndex;
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	assert(cfgRef->nodeList != NULL);

	layerIndex = hiddenLayerIndex + 1;
	
	assert(layerIndex > 0 && layerIndex < cfgRef->layers - 1);

	return cfgRef->nodeList[layerIndex];
}

int ann_config_get_transfer_func(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	return cfgRef->transferFuncIndex;
}

double ann_config_get_learningRate(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	return cfgRef->learningRate;
}

double ann_config_get_momentumCoef(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	return cfgRef->momentumCoef;
}

double ann_get_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex)
{
	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* preLayer;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;
	
	annRef = ann;
	cfgRef = &annRef->config;

	// Checking
	assert(annRef->layerList != NULL);
	assert(layerIndex > 0 && layerIndex < cfgRef->layers);
	
	preLayer = &annRef->layerList[layerIndex - 1];
	layerRef = &annRef->layerList[layerIndex];

	assert(preNodeIndex >= 0 && preNodeIndex < preLayer->nodeCount);
	assert(nodeIndex >= 0 && nodeIndex < layerRef->nodeCount);

	return layerRef->nodeList[nodeIndex].weight[preNodeIndex];
}

double ann_get_threshold(ann_t ann, int layerIndex, int nodeIndex)
{
	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;
	
	annRef = ann;
	cfgRef = &annRef->config;

	// Checking
	assert(annRef->layerList != NULL);
	assert(layerIndex >= 0 && layerIndex < cfgRef->layers);
	
	layerRef = &annRef->layerList[layerIndex];

	assert(nodeIndex >= 0 && nodeIndex < layerRef->nodeCount);

	return layerRef->nodeList[nodeIndex].threshold;
}

