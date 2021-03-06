#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "ann.h"
#include "ann_private.h"

#define NUM_PRECISION 1000
#define NUM_MAX 1
#define NUM_MIN -1

float ann_rand()
{
    int randRange;

    randRange = (NUM_MAX - NUM_MIN) * NUM_PRECISION + 1;

    return (float)(rand() % randRange) / (float)(NUM_PRECISION) +
           (float)NUM_MIN;
}

void ann_rand_network(ann_t ann)
{
    ann_rand_weight(ann);
    ann_rand_threshold(ann);
    rnn_rand_recurrent_weight(ann);
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

    for (i = 1; i < cfgRef->layers; i++)
    {
        for (j = 0; j < layerRef[i].nodeCount; j++)
        {
            for (k = 0; k < layerRef[i - 1].nodeCount; k++)
            {
                layerRef[i].nodeList[j].weight[k] = ann_rand();
            }
        }
    }
}

void rnn_rand_recurrent_weight(ann_t ann)
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

    if (cfgRef->layers >= 3)
    {
        for (i = 0; i < layerRef[cfgRef->layers - 2].nodeCount; i++)
        {
            for (j = 0; j < layerRef[1].nodeCount; j++)
            {
                layerRef[1].nodeList[j].rWeight[i] = ann_rand();
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

    for (i = 1; i < cfgRef->layers; i++)
    {
        for (j = 0; j < layerRef[i].nodeCount; j++)
        {
            layerRef[i].nodeList[j].threshold = ann_rand();
        }
    }
}
