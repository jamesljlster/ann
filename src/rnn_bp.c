#include <stdlib.h>
#include <string.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

void rnn_bptt_erase(ann_t ann)
{
	int i, j, k;
	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	LOG("enter");

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Reset queue length
	annRef->queueHead = 0;
	annRef->queueTail = 0;

	// Clear common delta
	for(i = cfgRef->layers - 1; i > 0; i--)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			layerRef[i].nodeList[j].thresholdDelta = 0;
			for(k = 0; k < layerRef[i - 1].nodeCount; k++)
			{
				layerRef[i].nodeList[j].weightDelta[k] = 0;
			}
		}
	}

	// Clear recurrent delta
	for(i = 0; i < layerRef[cfgRef->layers - 2].nodeCount; i++)
	{
		for(j = 0; j < layerRef[1].nodeCount; j++)
		{
			layerRef[1].nodeList[j].rWeightDelta[i] = 0;
		}
	}

	LOG("exit");
}

void rnn_bptt_adjust_network(ann_t ann, double learningRate, double momentumCoef, double gradLimit)
{
	int i, j, k;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	double calcTmp;

	LOG("enter");

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Adjust network
	for(i = cfgRef->layers - 1; i > 0; i--)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			// Adjust threshold
			if(layerRef[i].nodeList[j].thresholdDelta > gradLimit)
			{
				layerRef[i].nodeList[j].thresholdDelta = gradLimit;
			}
			else if(layerRef[i].nodeList[j].thresholdDelta < -gradLimit)
			{
				layerRef[i].nodeList[j].thresholdDelta = -gradLimit;
			}

			calcTmp = layerRef[i].nodeList[j].threshold + learningRate * layerRef[i].nodeList[j].thresholdDelta + momentumCoef * layerRef[i].nodeList[j].deltaTh;
			layerRef[i].nodeList[j].deltaTh = calcTmp - layerRef[i].nodeList[j].threshold;
			layerRef[i].nodeList[j].threshold = calcTmp;

			// Adjust weight
			for(k = 0; k < layerRef[i - 1].nodeCount; k++)
			{
				if(layerRef[i].nodeList[j].weightDelta[k] > gradLimit)
				{
					layerRef[i].nodeList[j].weightDelta[k] = gradLimit;
				}
				else if(layerRef[i].nodeList[j].weightDelta[k] < -gradLimit)
				{
					layerRef[i].nodeList[j].weightDelta[k] = -gradLimit;
				}

				calcTmp = layerRef[i].nodeList[j].weight[k] + learningRate * layerRef[i].nodeList[j].weightDelta[k] + momentumCoef * layerRef[i].nodeList[j].deltaW[k];
				layerRef[i].nodeList[j].deltaW[k] = calcTmp - layerRef[i].nodeList[j].weight[k];
				layerRef[i].nodeList[j].weight[k] = calcTmp;
			}
		}
	}

	// Adjust recurrent weight
	for(i = 0; i < layerRef[cfgRef->layers - 2].nodeCount; i++)
	{
		for(j = 0; j < layerRef[1].nodeCount; j++)
		{
			if(layerRef[1].nodeList[j].rWeightDelta[i] > gradLimit)
			{
				layerRef[1].nodeList[j].rWeightDelta[i] = gradLimit;
			}
			else if(layerRef[1].nodeList[j].rWeightDelta[i] < -gradLimit)
			{
				layerRef[1].nodeList[j].rWeightDelta[i] = -gradLimit;
			}

			calcTmp = layerRef[1].nodeList[j].rWeight[i] + learningRate * layerRef[1].nodeList[j].rWeightDelta[i] + momentumCoef * layerRef[1].nodeList[j].deltaRW[i];
			layerRef[1].nodeList[j].deltaRW[i] = calcTmp - layerRef[1].nodeList[j].rWeight[i];
			layerRef[1].nodeList[j].rWeight[i] = calcTmp;
		}
	}

	LOG("exit");
}

int rnn_bptt_set_max_timestep(ann_t ann, int timeStep)
{
	int i, j;
	int retValue = ANN_NO_ERROR;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	double* tmpPtr = NULL;

	LOG("enter");

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Re-Allocate queue space
	for(i = 0; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			tmpPtr = realloc(layerRef[i].nodeList[j].outputQueue, timeStep * sizeof(double));
			if(tmpPtr == NULL)
			{
				retValue = ANN_MEM_FAILED;
				goto RET;
			}
			else
			{
				layerRef[i].nodeList[j].outputQueue = tmpPtr;
			}

			tmpPtr = realloc(layerRef[i].nodeList[j].sCalcQueue, timeStep * sizeof(double));
			if(tmpPtr == NULL)
			{
				retValue = ANN_MEM_FAILED;
				goto RET;
			}
			else
			{
				layerRef[i].nodeList[j].sCalcQueue = tmpPtr;
			}
		}
	}

	// Set queue size
	annRef->queueSize = timeStep;

RET:
	LOG("exit");
	return retValue;
}

void rnn_bptt_sum_gradient(ann_t ann, double* dError)
{
	int i, j, k, re;
	int indexTmp, queIndex, quePreIndex;
	double calcTmp;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	int queueLen = 0;

	LOG("enter");

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Update bptt queue
	annRef->queueHead = (annRef->queueHead + 1) % annRef->queueSize;
	if(annRef->queueHead == annRef->queueTail)
	{
		annRef->queueTail = (annRef->queueTail + 1) % annRef->queueSize;
	}

	// Find queue length
	queueLen = annRef->queueHead - annRef->queueTail + 1;
	if(queueLen <= 0)
	{
		queueLen = queueLen + annRef->queueSize;
	}

	// Set queue value
	for(i = 0; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			layerRef[i].nodeList[j].outputQueue[annRef->queueHead] = layerRef[i].nodeList[j].output;
			layerRef[i].nodeList[j].sCalcQueue[annRef->queueHead] = layerRef[i].nodeList[j].sCalc;
		}
	}

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

	// Find delta: hidden layer
	for(re = queueLen - 1; re >= 0; re--)
	{
		// Set queue index
		queIndex = (re - annRef->queueTail + annRef->queueSize) % annRef->queueSize;
		if(re == queueLen - 1)
		{
			// Backpropagation form output layer
			for(i = cfgRef->layers - 2; i > 0; i--)
			{
				for(j = 0; j < layerRef[i].nodeCount; j++)
				{
					calcTmp = 0;
					for(k = 0; k < layerRef[i + 1].nodeCount; k++)
					{
						calcTmp += layerRef[i + 1].nodeList[k].delta * layerRef[i + 1].nodeList[k].weight[j];
					}
					layerRef[i].nodeList[j].delta = calcTmp * layerRef[i].dActiveFunc(layerRef[i].nodeList[j].sCalcQueue[queIndex]);
				}
			}

		}
		else
		{
			// Backup recurrent delta
			for(j = 0; j < layerRef[1].nodeCount; j++)
			{
				layerRef[1].nodeList[j].deltaHold = layerRef[1].nodeList[j].delta;
				//deltaHold[j] = layerRef[1].nodeList[j].delta;
			}

			// Backpropagation form recurrent factor
			for(i = cfgRef->layers - 2; i > 0; i--)
			{
				for(j = 0; j < layerRef[i].nodeCount; j++)
				{
					if(i == cfgRef->layers - 2)
					{
						// Recurrent factor
						calcTmp = 0;
						for(k = 0; k < layerRef[1].nodeCount; k++)
						{
							calcTmp += layerRef[1].nodeList[k].deltaHold * layerRef[1].nodeList[k].rWeight[j];
							//calcTmp += deltaHold[k] * layerRef[1].nodeList[k].rWeight[j];
						}
						layerRef[i].nodeList[j].delta = calcTmp * layerRef[i].dActiveFunc(layerRef[i].nodeList[j].sCalcQueue[queIndex]);
					}
					else
					{
						// Common factor
						calcTmp = 0;
						for(k = 0; k < layerRef[i + 1].nodeCount; k++)
						{
							calcTmp += layerRef[i + 1].nodeList[k].delta * layerRef[i + 1].nodeList[k].weight[j];
						}
						layerRef[i].nodeList[j].delta = calcTmp * layerRef[i].dActiveFunc(layerRef[i].nodeList[j].sCalcQueue[queIndex]);
					}
				}
			}
		}

		// Sum adjust amount
		for(i = cfgRef->layers - 2; i > 0; i--)
		{
			for(j = 0; j < layerRef[i].nodeCount; j++)
			{
				// Find threshold adjust amount
				layerRef[i].nodeList[j].thresholdDelta += layerRef[i].nodeList[j].delta;

				// Find weight adjust amount
				for(k = 0; k < layerRef[i - 1].nodeCount; k++)
				{
					layerRef[i].nodeList[j].weightDelta[k] += layerRef[i].nodeList[j].delta * layerRef[i - 1].nodeList[k].outputQueue[queIndex];
				}

				// Find recurrent weight adjust amount
				quePreIndex = (re - 1 - annRef->queueTail + annRef->queueSize) % annRef->queueSize;
				if(i == 1 && re > 0)
				{
					indexTmp = cfgRef->layers - 2;
					for(k = 0; k < layerRef[indexTmp].nodeCount; k++)
					{
						layerRef[i].nodeList[j].rWeightDelta[k] += layerRef[i].nodeList[j].delta * layerRef[indexTmp].nodeList[k].outputQueue[quePreIndex];
					}
				}
			}
		}
	}

	LOG("exit");
}

