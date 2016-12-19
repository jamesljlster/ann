#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int ann_clone_config(struct ANN_CONFIG_STRUCT* dst, struct ANN_CONFIG_STRUCT* src)
{
	int i;

	dst->inputs = src->inputs;
	dst->outputs = src->outputs;
	dst->layers = src->layers;
	dst->transferFuncIndex = src->transferFuncIndex;

	dst->learningRate = src->learningRate;
	dst->momentumCoef = src->momentumCoef;

	dst->nodeList = calloc(dst->layers, sizeof(int));
	if(dst->nodeList == NULL)
		return ANN_MEM_FAILED;
	
	for(i = 0; i < dst->layers; i++)
		dst->nodeList[i] = src->nodeList[i];

	return ANN_NO_ERROR;
}
