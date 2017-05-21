#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

void rnn_bptt_forget(ann_t ann)
{

}

void rnn_bptt_adjust_network(ann_t ann, double learningRate, double momentumCoef)
{

}

int rnn_bptt_sum_delta(ann_t ann, double learningRate, double* dError)
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
		}
	}

	// Update queue length
	annRef->queueLen++;

	// Find network adjust delta: Output layer
	indexTmp = cfgRef->layers - 1;
	for(j = 0; j < layerRef[indexTmp].nodeCount; j++)
	{
		// Find delta
		layerRef[indexTmp].nodeList[j].delta = dError[j] * layerRef[indexTmp].dActiveFunc(layerRef[indexTmp].nodeList[j].sCalc);

		// Find threshold adjust amount
		layerRef[indexTmp].nodeList[j].thresholdDelta += layerRef[indexTmp].nodeList[j].delta;

		// Find weight adjust amount
		for(k = 0; k < layerRef[indexTmp - 1].nodeCount; k++)
		{
			layerRef[indexTmp].nodeList[j].weightDelta[k] += layerRef[indexTmp].nodeList[j].delta * layerRef[indexTmp - 1].nodeList[k].output;
		}
	}

	// Find network adjust delta: Recurrent hidden layers
	if(cfgRef->layers == 3)
	{
		// Allocate delta hold list
		deltaHold = calloc(layerRef[1].nodeCount, sizeof(double));
		if(deltaHold == NULL)
		{
			retValue = ANN_MEM_FAILED;
			goto RET;
		}

		// Find delta: recurrent
		for(re = annRef->queueLen - 1; re >= 0; re--)
		{
			// Backup hidden layer recurrent delta
			for(j = 0; j < layerRef[1].nodeCount; j++)
			{
				deltaHold[j] = layerRef[1].nodeList[j].delta;
			}

			// Delta calculation
			for(j = 0; j < layerRef[1].nodeCount; j++)
			{
				if(re == annRef->queueLen - 1)
				{
					calcTmp = 0;
					for(k = 0; k < layerRef[2].nodeCount; k++)
					{
						calcTmp += layerRef[2].nodeList[k].delta * layerRef[2].nodeList[k].weight[j];
					}
					layerRef[1].nodeList[j].delta = calcTmp * layerRef[1].dActiveFunc(layerRef[1].nodeList[j].sCalc);
				}
				else
				{
					calcTmp = 0;
					for(k = 0; k < layerRef[1].nodeCount; k++)
					{
						calcTmp += deltaHold[k] * layerRef[1].nodeList[k].rWeight[j];
					}
					layerRef[1].nodeList[j].delta = calcTmp * layerRef[1].dActiveFunc(layerRef[1].nodeList[j].sCalcQueue[re]);
				}
			}

			// Find threshold adjust amount
			layerRef[1].nodeList[j].thresholdDelta += layerRef[1].nodeList[j].delta;

			// Find weight and recurrent adjust amount
			for(k = 0; k < layerRef[1].nodeCount; k++)
			{
				layerRef[1].nodeList[j].weightDelta[k] += layerRef[1].nodeList[j].delta * layerRef[0].nodeList[k].outputQueue[re];

				if(re - 1 >= 0)
				{
					layerRef[1].nodeList[j].rWeightDelta[k] += layerRef[1].nodeList[j].delta * layerRef[1].nodeList[k].outputQueue[re - 1];
				}
			}
		}

		// Cleanup
		free(deltaHold);
	}
	else if(cfgRef->layers > 3)
	{
		// Find delta: recurrent
		for(re = annRef->queueLen - 1; re >= 0; re--)
		{
			for(i = cfgRef->layers - 2; i > 0; i--)
			{
				// Delta calculation
				for(j = 0; j < layerRef[i].nodeCount; j++)
				{
					if(i == cfgRef->layers - 2)
					{
						if(re == annRef->queueLen - 1)
						{
							indexTmp = cfgRef->layers - 1;
							calcTmp = 0;
							for(k = 0; k < layerRef[indexTmp].nodeCount; k++)
							{
								calcTmp += layerRef[indexTmp].nodeList[k].delta * layerRef[indexTmp].nodeList[k].weight[j];
							}
							layerRef[i].nodeList[j].delta = calcTmp * layerRef[i].dActiveFunc(layerRef[i].nodeList[j].sCalc);
						}
						else
						{
							calcTmp = 0;
							for(k = 0; k < layerRef[1].nodeCount; k++)
							{
								calcTmp += deltaHold[k] * layerRef[1].nodeList[k].rWeight[j];
							}
							layerRef[i].nodeList[j].delta = calcTmp * layerRef[i].dActiveFunc(layerRef[i].nodeList[j].sCalcQueue[re]);
						}
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

				// Find threshold adjust amount
				layerRef[i].nodeList[j].thresholdDelta += layerRef[i].nodeList[j].delta;

				// Find weight adjust amount
				for(k = 0; k < layerRef[indexTmp - 1].nodeCount; k++)
				{
					layerRef[1].nodeList[j].weightDelta[k] += layerRef[1].nodeList[j].delta * layerRef[indexTmp - 1].nodeList[k].outputQueue[re];
				}

				// Find recurrent adjust amount
				if(i == 1 && re - 1 >= 0)
				{
					layerRef[1].nodeList[j].rWeightDelta[k] += layerRef[1].nodeList[j].delta * layerRef[1].nodeList[k].outputQueue[re - 1];
				}
			}
		}
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
