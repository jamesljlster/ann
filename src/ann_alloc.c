#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"
#include "ann_builtin_math.h"

#include "debug.h"

int ann_allocate_network(struct ANN_STRUCT* sptr)
{
	int i, j;
	int retValue = ANN_NO_ERROR;

	int layers;
	int* nodeList;
	int* tFuncList;
	
	void* allocTmp = NULL;

	struct ANN_LAYER* tmpLayer = NULL;

	LOG("enter");

	// Checking
	layers = sptr->config.layers;
	nodeList = sptr->config.nodeList;
	tFuncList = sptr->config.tFuncList;
	if(layers < 2 || nodeList == NULL || tFuncList == NULL)
	{
		LOG("Checking failed");
		retValue = ANN_INVALID_ARG;
		goto RET;
	}

	// Allocate network
	tmpLayer = calloc(layers, sizeof(struct ANN_LAYER));
	if(tmpLayer == NULL)
	{
		LOG("calloc failed with arg: layers = %d", layers);
		retValue = ANN_MEM_FAILED;
		goto ERR;
	}

	for(i = 0; i < layers; i++)
	{
		// Check transfer funciont setting
		if(tFuncList[i] < 0 || tFuncList[i] >= ANN_TFUNC_AMOUNT)
		{
			LOG("Checking failed");
			retValue = ANN_INVALID_ARG;
			goto ERR;
		}

		tmpLayer[i].activeFunc = ann_transfer_list[tFuncList[i]];
		tmpLayer[i].dActiveFunc = ann_transfer_derivative_list[tFuncList[i]];
		tmpLayer[i].nodeCount = nodeList[i];

		allocTmp = calloc(nodeList[i], sizeof(struct ANN_NODE));
		if(allocTmp == NULL)
		{
			LOG("calloc failed with arg: nodeList[%d] = %d", i, nodeList[i]);
			retValue = ANN_MEM_FAILED;
			goto ERR;
		}
		else
		{
			tmpLayer[i].nodeList = allocTmp;

			for(j = 0; j < nodeList[i]; j++)
			{
				if(i > 0)
				{
					allocTmp = calloc(nodeList[i - 1], sizeof(double));
					if(allocTmp == NULL)
					{
						LOG("calloc failed with arg: nodeList[%d] = %d", i - 1, nodeList[i - 1]);
						retValue = ANN_MEM_FAILED;
						goto ERR;
					}
					else
					{
						tmpLayer[i].nodeList[j].weight = allocTmp;
					}

					allocTmp = calloc(nodeList[i - 1], sizeof(double));
					if(allocTmp == NULL)
					{
						LOG("calloc failed with arg: nodeList[%d] = %d", i - 1, nodeList[i - 1]);
						retValue = ANN_MEM_FAILED;
						goto ERR;
					}
					else
					{
						tmpLayer[i].nodeList[j].weightDelta = allocTmp;
					}

					allocTmp = calloc(nodeList[i - 1], sizeof(double));
					if(allocTmp == NULL)
					{
						LOG("calloc failed with arg: nodeList[%d] = %d", i - 1, nodeList[i - 1]);
						retValue = ANN_MEM_FAILED;
						goto ERR;
					}
					else
					{
						tmpLayer[i].nodeList[j].deltaW = allocTmp;
					}
				}
			}
		}
	}

	// Allocate recurrent weight
	if(layers > 2)
	{
		for(i = 0; i < nodeList[1]; i++)
		{
			allocTmp = calloc(nodeList[layers - 2], sizeof(double));
			if(allocTmp == NULL)
			{
				retValue = ANN_MEM_FAILED;
				goto ERR;
			}
			else
			{
				tmpLayer[1].nodeList[i].rWeight = allocTmp;
			}

			allocTmp = calloc(nodeList[layers - 2], sizeof(double));
			if(allocTmp == NULL)
			{
				retValue = ANN_MEM_FAILED;
				goto ERR;
			}
			else
			{
				tmpLayer[1].nodeList[i].rWeightDelta = allocTmp;
			}

			allocTmp = calloc(nodeList[layers - 2], sizeof(double));
			if(allocTmp == NULL)
			{
				retValue = ANN_MEM_FAILED;
				goto ERR;
			}
			else
			{
				tmpLayer[1].nodeList[i].deltaRW = allocTmp;
			}
		}
	}

	// Assign value
	sptr->layerList = tmpLayer;

	goto RET;

ERR:
	if(tmpLayer != NULL)
	{
		for(i = 0; i < layers; i++)
			ann_delete_layer(tmpLayer);

		free(tmpLayer);
	}

RET:
	LOG("exit");
	return retValue;
}

