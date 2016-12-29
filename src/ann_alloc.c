#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"
#include "ann_builtin_math.h"

#include "debug.h"

int ann_allocate_network(struct ANN_STRUCT* sptr)
{
	int i, j;
	int retValue = ANN_NO_ERROR;

	int tfunc;
	int layers;
	int* nodeList;
	
	void* allocTmp = NULL;

	struct ANN_LAYER* tmpLayer = NULL;

	log("enter");

	// Checking
	layers = sptr->config.layers;
	tfunc = sptr->config.transferFuncIndex;
	nodeList = sptr->config.nodeList;
	if(layers <= 0 || nodeList == NULL || tfunc >= 5 || tfunc < 0)
	{
		log("Checking failed");
		retValue = ANN_INFO_NOT_FOUND;
		goto RET;
	}

	// Allocate network
	tmpLayer = calloc(layers, sizeof(struct ANN_LAYER));
	if(tmpLayer == NULL)
	{
		log("calloc failed with arg: layers = %d", layers);
		retValue = ANN_MEM_FAILED;
		goto ERR;
	}

	for(i = 0; i < layers; i++)
	{
		tmpLayer[i].activeFunc = ann_transfer_list[tfunc];
		tmpLayer[i].dActiveFunc = ann_transfer_derivative_list[tfunc];
		tmpLayer[i].nodeCount = nodeList[i];

		allocTmp = calloc(nodeList[i], sizeof(struct ANN_NODE));
		if(allocTmp == NULL)
		{
			log("calloc failed with arg: nodeList[%d] = %d", i, nodeList[i]);
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
						log("calloc failed with arg: nodeList[%d] = %d", i - 1, nodeList[i - 1]);
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
						log("calloc failed with arg: nodeList[%d] = %d", i - 1, nodeList[i - 1]);
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
	log("exit");
	return retValue;
}
