#include <stdlib.h>
#include <assert.h>

#include "ann.h"
#include "ann_private.h"
#include "ann_builtin_math.h"

#include "debug.h"

#define INIT_NODES	10

void ann_set_learning_rate(ann_t ann, double learningRate)
{
	struct ANN_STRUCT* annRef = ann;
	annRef->config.learningRate = learningRate;
}

void ann_set_momentum_coef(ann_t ann, double momentumCoef)
{
	struct ANN_STRUCT* annRef = ann;
	annRef->config.momentumCoef = momentumCoef;
}

void ann_config_set_learning_rate(ann_config_t config, double learningRate)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;
	
	cfgRef->learningRate = learningRate;
}

void ann_config_set_momentum_coef(ann_config_t config, double momentumCoef)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;
	
	cfgRef->momentumCoef = momentumCoef;
}

int ann_config_set_inputs(ann_config_t config, int inputs)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	if(inputs <= 0)
	{
		return ANN_INVALID_ARG;
	}
	
	cfgRef->inputs = inputs;
	
	if(cfgRef->nodeList != NULL)
	{
		cfgRef->nodeList[0] = inputs;
	}

	return ANN_NO_ERROR;
}

int ann_config_set_outputs(ann_config_t config, int outputs)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	if(outputs <= 0)
	{
		return ANN_INVALID_ARG;
	}
	
	cfgRef->outputs = outputs;

	if(cfgRef->nodeList != NULL)
	{
		cfgRef->nodeList[cfgRef->layers - 1] = outputs;
	}

	return ANN_NO_ERROR;
}

int ann_config_set_hidden_layers(ann_config_t config, int hiddenLayers)
{
	int i;
	int retValue = ANN_NO_ERROR;
	int tmpLayerCount;
	int preLayerCount;
	int* tmpList = NULL;
	int* tmpTFuncList = NULL;

	struct ANN_CONFIG_STRUCT* cfgRef = config;
	
	LOG("enter");

	// Checking
	if(hiddenLayers <= 0)
	{
		retValue = ANN_INVALID_ARG;
		goto RET;
	}

	tmpLayerCount = hiddenLayers + 2;
	
	// Memory allocation: Node list
	tmpList = calloc(tmpLayerCount, sizeof(int));
	if(tmpList == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto ERR;
	}
	else
	{
		// Set default values
		tmpList[0] = cfgRef->inputs;
		tmpList[tmpLayerCount - 1] = cfgRef->outputs;

		for(i = 1; i < tmpLayerCount - 1; i++)
		{
			tmpList[i] = INIT_NODES;
		}
	}

	// Memory allocation: Transfer function list
	tmpTFuncList = calloc(tmpLayerCount, sizeof(int));
	if(tmpTFuncList == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto ERR;
	}

	// Copy old values
	preLayerCount = cfgRef->layers;
	if(cfgRef->nodeList != NULL)
	{
		for(i = 1; i < preLayerCount - 1; i++)
		{
			tmpList[i] = cfgRef->nodeList[i];
		}
		
		free(cfgRef->nodeList);
	}

	if(cfgRef->tFuncList != NULL)
	{
		for(i = 0; i < preLayerCount; i++)
		{
			tmpTFuncList[i] = cfgRef->tFuncList[i];
		}

		free(cfgRef->tFuncList);
	}
	else
	{
		// Set default values
		tmpTFuncList[0] = ANN_IDENTITY;

		cfgRef->tFuncRoot = ANN_TFUNC_MULTIPLE;
	}

	// Assign values
	cfgRef->nodeList = tmpList;
	cfgRef->tFuncList = tmpTFuncList;
	cfgRef->layers = tmpLayerCount;

	tmpList = NULL;
	tmpTFuncList = NULL;

	goto RET;

ERR:
	if(tmpList != NULL)
	{
		free(tmpList);
	}

	if(tmpTFuncList != NULL)
	{
		free(tmpTFuncList);
	}

RET:
	LOG("exit");
	return retValue;
}

int ann_config_set_hidden_nodes(ann_config_t config, int hiddenLayerIndex, int nodes)
{
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	// Checking
	if(hiddenLayerIndex < 0 || hiddenLayerIndex >= cfgRef->layers - 2)
		return ANN_OUT_OF_RANGE;

	if(nodes <= 0)
	{
		return ANN_INVALID_ARG;
	}

	cfgRef->nodeList[hiddenLayerIndex + 1] = nodes;

	return ANN_NO_ERROR;
}

int ann_config_set_transfer_func_all(ann_config_t config, int tFuncIndex)
{
	int i;
	struct ANN_CONFIG_STRUCT* cfgRef = config;

	// Checking
	if(tFuncIndex < 0 || tFuncIndex >= ANN_TFUNC_AMOUNT)
	{
		return ANN_INVALID_ARG;
	}
	
	for(i = 0; i < cfgRef->layers; i++)
	{
		cfgRef->tFuncList[i] = tFuncIndex;
	}

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

int ann_set_recurrent_weight_struct(struct ANN_STRUCT* sptr, int preNodeIndex, int nodeIndex, double value)
{
	struct ANN_LAYER* preLayerRef;
	struct ANN_LAYER* layerRef;
	int layers;

	// Checking
	assert(sptr->layerList != NULL);
	layers = sptr->config.layers;
	if(layers <= 2)
	{
		return ANN_INVALID_ARG;
	}

	// Set layer reference
	preLayerRef = &sptr->layerList[layers - 2];
	layerRef = &sptr->layerList[1];

	if(preNodeIndex < 0 || preNodeIndex >= preLayerRef->nodeCount)
		return ANN_OUT_OF_RANGE;
	if(nodeIndex < 0 || nodeIndex >= layerRef->nodeCount)
		return ANN_OUT_OF_RANGE;

	assert(layerRef->nodeList[nodeIndex].rWeight != NULL);
	layerRef->nodeList[nodeIndex].rWeight[preNodeIndex] = value;

	return ANN_NO_ERROR;
}

int ann_set_threshold_struct(struct ANN_STRUCT* sptr, int layerIndex, int nodeIndex, double value)
{
	struct ANN_LAYER* layerRef;

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

