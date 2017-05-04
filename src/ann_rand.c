#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "ann.h"
#include "ann_private.h"

#define NUM_PRECISION	1000
#define NUM_MAX			1
#define	NUM_MIN			-1

double ann_rand()
{
	int randRange;

	randRange = (NUM_MAX - NUM_MIN) * NUM_PRECISION + 1;

	return (double)(rand() % randRange) / (double)(NUM_PRECISION) + (double)NUM_MIN;
}

void ann_rand_weight(ann_t ann)
{
	int i, j, k;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	assert(layerRef != NULL);

	srand(time(NULL));

	for(i = 1; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			for(k = 0; k < layerRef[i - 1].nodeCount; k++)
			{
				layerRef[i].nodeList[j].weight[k] = ann_rand();
			}
		}
	}
}

void ann_rand_threshold(ann_t ann)
{
	int i, j;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	assert(layerRef != NULL);

	srand(time(NULL));

	for(i = 1; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			layerRef[i].nodeList[j].threshold = ann_rand();
		}
	}
}
