#include <stdlib.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int ann_backpropagation(ann_t ann, double learningRate, double momentumCoef, double* dError)
{
	int i, j, k;
	int retValue = ANN_NO_ERROR;
	
	double calcTmp;

	double** deltaList = NULL;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;
	
	log("enter");

	// Get reference
	annRef = ann;
	layerRef = annRef->layerList;
	cfgRef = &annRef->config;

	// Memory allocation
	deltaList = calloc(cfgRef->layers, sizeof(double*));
	if(deltaList == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto RET;
	}

	for(i = 0; i < cfgRef->layers; i++)
	{
		deltaList[i] = calloc(layerRef[i].nodeCount, sizeof(double));
		if(deltaList[i] == NULL)
		{
			retValue = ANN_MEM_FAILED;
			goto RET;
		}
	}

	// Process delta list
	for(i = cfgRef->layers - 1; i > 0; i--)
	{
		if(i == cfgRef->layers - 1)
		{
			for(j = 0; j < layerRef[i].nodeCount; j++)
			{
				deltaList[i][j] = dError[j] * layerRef[i].dActiveFunc(layerRef[i].nodeList[j].sCalc);
			}
		}
		else
		{
			for(j = 0; j < layerRef[i].nodeCount; j++)
			{
				calcTmp = 0;
				for(k = 0; k < layerRef[i + 1].nodeCount; k++)
				{
					calcTmp += deltaList[i + 1][k] * layerRef[i + 1].nodeList[k].weight[j];
				}
				deltaList[i][j] = calcTmp * layerRef[i].dActiveFunc(layerRef[i].nodeList[j].sCalc);
			}
		}
	}

	// Adjust
	for(i = cfgRef->layers - 1; i > 0; i--)
	{
		for(j = 0; j < layerRef[i].nodeCount; j++)
		{
			// Adjust threshold
			calcTmp = layerRef[i].nodeList[j].threshold + learningRate * deltaList[i][j] + momentumCoef * layerRef[i].nodeList[j].deltaTh;
			layerRef[i].nodeList[j].deltaTh = calcTmp - layerRef[i].nodeList[j].threshold;
			layerRef[i].nodeList[j].threshold = calcTmp;

			// Adjust weight
			for(k = 0; k < layerRef[i - 1].nodeCount; k++)
			{
				calcTmp = layerRef[i].nodeList[j].weight[k] + learningRate * deltaList[i][j] * layerRef[i - 1].nodeList[k].output + momentumCoef * layerRef[i].nodeList[j].deltaW[k];
				layerRef[i].nodeList[j].deltaW[k] = calcTmp - layerRef[i].nodeList[j].weight[k];
				layerRef[i].nodeList[j].weight[k] = calcTmp;
			}
		}
	}

RET:
	if(deltaList != NULL)
	{
		for(i = 0; i < cfgRef->layers; i++)
		{
			if(deltaList[i] != NULL)
				free(deltaList[i]);
		}
		free(deltaList);
	}
	
	log("exit");
	return retValue;
}
