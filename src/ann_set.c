#include <assert.h>

#include "ann.h"
#include "ann_private.h"

void ann_set_weight(struct ANN_STRUCT* sptr, int layerIndex, int preNodeIndex, int nodeIndex, double value)
{
	struct ANN_LAYER* preLayerRef;
	struct ANN_LAYER* layerRef;
	struct ANN_NODE* nodeRef;

	// Checking
	assert(sptr->layerList != NULL);
	assert(layerIndex < sptr->config.layers && layerIndex > 0);
	
	preLayerRef = &sptr->layerList[layerIndex - 1];
	layerRef = &sptr->layerList[layerIndex];

	assert(preNodeIndex >= 0 && preNodeIndex < preLayerRef->nodeCount);
	assert(nodeIndex >= 0 && nodeIndex < layerRef->nodeCount);

	layerRef->nodeList[nodeIndex].weight[preNodeIndex] = value;
}

void ann_set_threshold(struct ANN_STRUCT* sptr, int layerIndex, int nodeIndex)
{
	struct ANN_LAYER* layerRef;
	struct ANN_NODE* nodeRef;

	// Checking
	assert(sptr->layerList != NULL);
	assert(layerIndex < sptr->config.layers && layerIndex > 0);
	
	layerRef = &sptr->layerList[layerIndex];

	assert(nodeIndex >= 0 && nodeIndex < layerRef->nodeCount);

	layerRef->nodeList[nodeIndex].threshold = value;
}

