#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int ann_config_clone(ann_config_t* dstCfgPtr, ann_config_t srcCfg)
{
	int iResult;
	int retValue = ANN_NO_ERROR;
	ann_config_t tmpCfg = NULL;

	// Allocate memory
	tmpCfg = malloc(sizeof(struct ANN_CONFIG_STRUCT));
	if(tmpCfg == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto RET;
	}

	// Clone config
	iResult = ann_clone_config_struct(tmpCfg, srcCfg);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Assig value
	*dstCfgPtr = tmpCfg;

RET:
	return retValue;
}

int ann_clone_config_struct(struct ANN_CONFIG_STRUCT* dst, struct ANN_CONFIG_STRUCT* src)
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

int ann_clone(ann_t* dstAnnPtr, ann_t srcAnn)
{
	int i, j, k;
	int iResult;
	int retValue = ANN_NO_ERROR;
	int inputs, outputs;
	int layers;
	double tmp;

	ann_t ann = NULL;
	ann_config_t srcCfg = NULL;

	// Get source config
	srcCfg = ann_get_config(srcAnn);

	// Create neural network
	iResult = ann_create(&ann, srcCfg);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Copy weight and threshold
	inputs = ann_config_get_inputs(srcCfg);
	outputs = ann_config_get_outputs(srcCfg);
	layers = ann_config_get_hidden_layers(srcCfg) + 2;
	for(i = 1; i < layers; i++)
	{
		if(i == layers - 1)
		{
			for(j = 0; j < outputs; j++)
			{
				for(k = 0; k < ann_config_get_hidden_nodes(srcCfg, i - 2); k++)
				{
					tmp = ann_get_weight(srcAnn, i, k, j);
					ann_set_weight(ann, i, k, j, tmp);
				}
				tmp = ann_get_threshold(srcAnn, i, j);
				ann_set_threshold(ann, i, j, tmp);
			}
		}
		else if(i == 1)
		{
			for(j = 0; j < ann_config_get_hidden_nodes(srcCfg, i - 1); j++)
			{
				for(k = 0; k < inputs; k++)
				{
					tmp = ann_get_weight(srcAnn, i, k, j);
					ann_set_weight(ann, i, k, j, tmp);
				}
				tmp = ann_get_threshold(srcAnn, i, j);
				ann_set_threshold(ann, i, j, tmp);
			}
		}
		else
		{
			for(j = 0; j < ann_config_get_hidden_nodes(srcCfg, i - 1); j++)
			{
				for(k = 0; k < ann_config_get_hidden_nodes(srcCfg, i - 2); k++)
				{
					tmp = ann_get_weight(srcAnn, i, k, j);
					ann_set_weight(ann, i, k, j, tmp);
				}
				tmp = ann_get_threshold(srcAnn, i, j);
				ann_set_threshold(ann, i, j, tmp);
			}
		}
	}

	// Assign value
	*dstAnnPtr = ann;

RET:
	return retValue;
}
