
#include "ann.h"
#include "ann_private.h"

#include "debug.h"

void ann_forward_computation(ann_t ann, double* input, double* output)
{
	int i, j;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Copy inputs
	for(i = 0; i < cfgRef->inputs; i++)
	{
		if(layerRef[0].activeFunc == NULL)
		{
			layerRef[0].nodeList[i].output = input[i];
		}
		else
		{
			layerRef[0].nodeList[i].output = layerRef[0].activeFunc(input[i]);
		}
	}
	
	// Calculation
	for(i = 1; i < cfgRef->layers; i++)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			int k;
			double calcTmp;

			calcTmp = 0;
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
}

