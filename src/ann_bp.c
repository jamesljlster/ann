#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int rnn_bptt(ann_t ann, double learningRate, double momentumCoef, double* dError)
{
	int i, j, k, re;
	int retValue = ANN_NO_ERROR;
	int indexTmp;
	double calcTmp;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	double* deltaHold = NULL;
	double* tmpPtr = NULL;
	int queueLen = 0;

	LOG("enter");

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Re-Allocate queue space and clear delta
	queueLen = annRef->queueLen;
	for(i = 0; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			tmpPtr = realloc(layerRef[i].nodeList[j].outputQueue, (queueLen + 1) * sizeof(double));
			if(tmpPtr == NULL)
			{
				retValue = ANN_MEM_FAILED;
				goto RET;
			}
			else
			{
				tmpPtr[queueLen] = layerRef[i].nodeList[j].output;
				layerRef[i].nodeList[j].outputQueue = tmpPtr;
			}

			tmpPtr = realloc(layerRef[i].nodeList[j].sCalcQueue, (queueLen + 1) * sizeof(double));
			if(tmpPtr == NULL)
			{
				retValue = ANN_MEM_FAILED;
				goto RET;
			}
			else
			{
				tmpPtr[queueLen] = layerRef[i].nodeList[j].sCalc;
				layerRef[i].nodeList[j].sCalcQueue = tmpPtr;
			}

			layerRef[i].nodeList[j].delta = 0;
		}
	}

	// Update queue length
	annRef->queueLen++;

	// Find network adjust delta: Output layer
	indexTmp = cfgRef->layers - 1;
	for(j = 0; j < layerRef[indexTmp].nodeCount; j++)
	{
		layerRef[indexTmp].nodeList[j].delta = dError[j] * layerRef[indexTmp].dActiveFunc(layerRef[indexTmp].nodeList[j].sCalc);
	}

	// Find network adjust delta: Hidden layers
	if(cfgRef->layers == 3)
	{
		// Allocate delta hold list
		deltaHold = calloc(layerRef[1].nodeCount, sizeof(double));
		if(deltaHold == NULL)
		{
			retValue = ANN_MEM_FAILED;
			goto RET;
		}

		// Find delta
		for(re = annRef->queueLen - 1; re >= 0; re--)
		{
			// Backup hidden layer recurrent delta
			for(j = 0; j < layerRef[1].nodeCount; j++)
			{
				deltaHold[j] = layerRef[1].nodeList[j].delta;
			}

		}

		// Cleanup
		free(deltaHold);
	}
	else if(cfgRef->layers > 3)
	{

	}

RET:

	LOG("exit");
	return retValue;
}

void ann_backpropagation(ann_t ann, double learningRate, double momentumCoef, double* dError)
{
	int i, j, k;
	
	double calcTmp;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;
	
	LOG("enter");

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Process delta list
	for(i = cfgRef->layers - 1; i > 0; i--)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			if(i == cfgRef->layers - 1)
			{
				layerRef[i].nodeList[j].delta = dError[j] * layerRef[i].dActiveFunc(layerRef[i].nodeList[j].sCalc);
			}
			else
			{
				calcTmp = 0;
				for(k = 0; k < layerRef[i + 1].nodeCount; k++)
				{
					calcTmp += layerRef[i + 1].nodeList[k].delta * layerRef[i + 1].nodeList[k].weight[j];
				}
				layerRef[i].nodeList[j].delta = calcTmp * layerRef[i].dActiveFunc(layerRef[i].nodeList[j].sCalc);
			}
		}
	}

	// Adjust
	for(i = cfgRef->layers - 1; i > 0; i--)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			// Adjust threshold
			calcTmp = layerRef[i].nodeList[j].threshold + learningRate * layerRef[i].nodeList[j].delta + momentumCoef * layerRef[i].nodeList[j].deltaTh;
			layerRef[i].nodeList[j].deltaTh = calcTmp - layerRef[i].nodeList[j].threshold;
			layerRef[i].nodeList[j].threshold = calcTmp;

			// Adjust weight
			for(k = 0; k < layerRef[i - 1].nodeCount; k++)
			{
				calcTmp = layerRef[i].nodeList[j].weight[k] + learningRate * layerRef[i].nodeList[j].delta * layerRef[i - 1].nodeList[k].output + momentumCoef * layerRef[i].nodeList[j].deltaW[k];
				layerRef[i].nodeList[j].deltaW[k] = calcTmp - layerRef[i].nodeList[j].weight[k];
				layerRef[i].nodeList[j].weight[k] = calcTmp;
			}
		}
	}

	LOG("exit");
}
