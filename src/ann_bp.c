#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int ann_backpropagation(ann_t ann, double learningRate, double momentumCoef, double* dError)
{
	int i, j;
	int retValue = ANN_NO_ERROR;

	double** delteList = NULL;

	struct ANN_STRUCT* annRef;
	struct ANN_LAYER* layerRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

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

	for(i = 0; i < cfgRef->layers; j++)
	{
		deltaList[i] = calloc(layerRef[i].nodeCount, sizeof(double));
		if(deltaList[i] == NULL)
		{
			retValue = ANN_MEM_FAILED;
			goto RET;
		}
	}

	// Process delta list
	for(i = cfgRef->layers - 1; i  > 0; i--)
	{
		if(i == cfgRef->layers - 1)
		{
			for(j = 0; j < layerRef[i].nodeCount; j++)
			{
				deltaList[i][j] = dError[j] * layerRef[i].dActiveFunc(layerRef[i].sCalc);
			}
		}
		else
		{
			for(j = 0; j < layerRef[i].nodeCount; j++)
			{
				int k;
				double calcTmp;

				calcTmp = 0;
				for(k = 0; k < layerRef[i + 1].nodeCount; k++)
				{
					calcTmp += deltaList[i + 1][k] * layerList[i + 1].nodeList[k].weight[j];
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
		free(delteList);
	}

	return retValue;
}
