#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

void rnn_forward_computation_erase(ann_t ann)
{
	int i;
	int indexTmp;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	LOG("enter");

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Clear recurrent hold
	indexTmp = cfgRef->layers - 2;
	for(i = 0; i < layerRef[indexTmp].nodeCount; i++)
	{
		layerRef[indexTmp].nodeList[i].output = 0;
	}

	LOG("exit");
}

void rnn_forward_computation(ann_t ann, double* input, double* output)
{
	int i, j, k;
	int indexTmp;
	double calcTmp;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	LOG("enter");

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Copy inputs
	for(i = 0; i < cfgRef->inputs; i++)
	{
		//layerRef[0].nodeList[i].output = layerRef[0].activeFunc(input[i]);
		layerRef[0].nodeList[i].output = input[i];
	}

	// Backup recurrent output
	indexTmp = cfgRef->layers - 2;
	for(i = 0; i < layerRef[indexTmp].nodeCount; i++)
	{
		layerRef[indexTmp].nodeList[i].rHold = layerRef[indexTmp].nodeList[i].output;
	}
	
	// Calculation
	for(i = 1; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			calcTmp = 0;

			// Recurrent factor
			if(i == 1)
			{
				for(k = 0; k < layerRef[indexTmp].nodeCount; k++)
				{
					calcTmp += layerRef[indexTmp].nodeList[k].rHold * layerRef[1].nodeList[j].rWeight[k];
				}
			}

			// Common factor
			for(k = 0; k < layerRef[i - 1].nodeCount; k++)
			{
				calcTmp += layerRef[i - 1].nodeList[k].output * layerRef[i].nodeList[j].weight[k];
			}

			layerRef[i].nodeList[j].sCalc = calcTmp + layerRef[i].nodeList[j].threshold;
			layerRef[i].nodeList[j].output = layerRef[i].activeFunc(layerRef[i].nodeList[j].sCalc);
		}
	}

	// Get output
	if(output != NULL)
	{
		for(i = 0; i < cfgRef->outputs; i++)
		{
			output[i] = layerRef[cfgRef->layers - 1].nodeList[i].output;
		}
	}

	LOG("exit");
}

