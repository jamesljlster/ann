#include <stdlib.h>
#include <assert.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

void ann_clear_momentum(ann_t ann)
{
	int i, j, k;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	assert(layerRef != NULL);

	for(i = 1; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			layerRef[i].nodeList[j].deltaTh = 0;
			for(k = 0; k < layerRef[i - 1].nodeCount; k++)
			{
				layerRef[i].nodeList[j].deltaW[k] = 0;
			}
		}
	}
}

void ann_zeromem(struct ANN_STRUCT* asPtr)
{
	asPtr->layerList = NULL;
	asPtr->queueLen = 0;
	ann_config_zeromem(&asPtr->config);
}

void ann_config_zeromem(struct ANN_CONFIG_STRUCT* cfgPtr)
{
	cfgPtr->inputs = 0;
	cfgPtr->outputs = 0;
	cfgPtr->layers = 0;
	cfgPtr->tFuncRoot = 0;
	
	cfgPtr->learningRate = 0;
	cfgPtr->momentumCoef = 0;

	cfgPtr->tFuncList = NULL;
	cfgPtr->nodeList = NULL;
}

void ann_zero_weight(ann_t ann)
{
	int i, j, k;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	assert(layerRef != NULL);

	for(i = 1; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			for(k = 0; k < layerRef[i - 1].nodeCount; k++)
			{
				layerRef[i].nodeList[j].weight[k] = 0;
			}
		}
	}
}

void ann_zero_threshold(ann_t ann)
{
	int i, j;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	assert(layerRef != NULL);

	for(i = 1; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			layerRef[i].nodeList[j].threshold = 0;
		}
	}
}

void rnn_zero_recurrent_weight(ann_t ann)
{
	int i, j;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	assert(layerRef != NULL);

	if(cfgRef->layers >= 3)
	{
		for(i = 0; i < layerRef[cfgRef->layers - 2].nodeCount; i++)
		{
			for(j = 0; j < layerRef[1].nodeCount; j++)
			{
				layerRef[1].nodeList[j].rWeight[i] = 0;
			}
		}
	}
}

