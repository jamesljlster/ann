#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int rnn_training_gradient(ann_t ann, double** inputList, double** desireList, double** outputList, double** errList, int timeStep, double deltaLimit)
{
	struct ANN_STRUCT* annRef = NULL;
	struct ANN_CONFIG_STRUCT* cfgRef = NULL;

	// Get referenct
	annRef = ann;
	cfgRef = &annRef->config;

	return rnn_training_gradient_custom(ann, cfgRef->learningRate, cfgRef->momentumCoef, inputList, desireList, outputList, errList, timeStep, deltaLimit);
}

int rnn_training_gradient_custom(ann_t ann, double learningRate, double momentumCoef, double** inputList, double** desireList, double** outputList, double** errList, int timeStep, double deltaLimit)
{
	int i, j;
	int iResult;
	int retValue = ANN_NO_ERROR;
	
	double* outputStore = NULL;
	double* errorStore = NULL;

	struct ANN_STRUCT* annRef = NULL;
	struct ANN_CONFIG_STRUCT* cfgRef = NULL;

	LOG("enter");

	// Get referenct
	annRef = ann;
	cfgRef = &annRef->config;

	// Memory allocation
	outputStore = calloc(cfgRef->outputs * timeStep, sizeof(double));
	errorStore = calloc(cfgRef->outputs * timeStep, sizeof(double));
	if(outputStore == NULL || errorStore == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto RET;
	}

	// Recurrent training
	for(i = 0; i < timeStep; i++)
	{
		// Forward computation
		ann_forward_computation(ann, inputList[i], &outputStore[i * cfgRef->outputs]);

		// Find error
		for(j = 0; j < cfgRef->outputs; j++)
		{
			errorStore[i * cfgRef->outputs + j] = desireList[i][j] - outputStore[i * cfgRef->outputs + j];
		}

		// Backpropagation
		iResult = rnn_bptt_sum_delta(ann, &errorStore[i * cfgRef->outputs]);
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}
	}

	// Adjust network
	rnn_bptt_adjust_network(ann, learningRate, momentumCoef, deltaLimit);

	// Erase
	rnn_bptt_erase(ann);
	rnn_forget(ann);

	// Copy values
	if(outputList != NULL)
	{
		for(i = 0; i < timeStep; i++)
		{
			for(j = 0; j < cfgRef->outputs; j++)
			{
				outputList[i][j] = outputStore[i * cfgRef->outputs + j];
			}
		}
	}

	if(errList != NULL)
	{
		for(i = 0; i < timeStep; i++)
		{
			for(j = 0; j < cfgRef->outputs; j++)
			{
				errList[i][j] = errorStore[i * cfgRef->outputs + j];
			}
		}
	}

RET:
	if(outputStore != NULL)
		free(outputStore);

	if(errorStore != NULL)
		free(errorStore);

	return retValue;
}

int ann_training_gradient_custom(ann_t ann, double learningRate, double momentumCoef, double* input, double* desire, double* output, double* err)
{
	int i;
	int retValue = ANN_NO_ERROR;
	
	double* outputStore = NULL;
	double* errorStore = NULL;

	struct ANN_STRUCT* annRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	LOG("enter");

	// Get reference
	annRef = ann;
	cfgRef = &annRef->config;

	// Memory allocation
	outputStore = calloc(cfgRef->outputs, sizeof(double));
	errorStore = calloc(cfgRef->outputs, sizeof(double));
	if(outputStore == NULL || errorStore == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto RET;
	}

	// Forward computation
	ann_forward_computation(ann, input, outputStore);

	// Find error
	for(i = 0; i < cfgRef->outputs; i++)
	{
		errorStore[i] = desire[i] - outputStore[i];
	}

	// Backpropagation
	ann_backpropagation(ann, learningRate, momentumCoef, errorStore);

	if(output != NULL)
		memcpy(output, outputStore, cfgRef->outputs * sizeof(double));

	if(err != NULL)
		memcpy(err, errorStore, cfgRef->outputs * sizeof(double));

RET:
	if(outputStore != NULL)
		free(outputStore);

	if(errorStore != NULL)
		free(errorStore);

	LOG("exit");
	return retValue;
}

int ann_training_gradient(ann_t ann, double* input, double* desire, double* output, double* err)
{
	int i;
	int retValue = ANN_NO_ERROR;
	
	double* outputStore = NULL;
	double* errorStore = NULL;

	struct ANN_STRUCT* annRef;
	struct ANN_CONFIG_STRUCT* cfgRef;

	LOG("enter");

	// Get reference
	annRef = ann;
	cfgRef = &annRef->config;

	// Memory allocation
	outputStore = calloc(cfgRef->outputs, sizeof(double));
	errorStore = calloc(cfgRef->outputs, sizeof(double));
	if(outputStore == NULL || errorStore == NULL)
	{
		retValue = ANN_MEM_FAILED;
		goto RET;
	}

	// Forward computation
	ann_forward_computation(ann, input, outputStore);

	// Find error
	for(i = 0; i < cfgRef->outputs; i++)
	{
		errorStore[i] = desire[i] - outputStore[i];
	}

	// Backpropagation
	ann_backpropagation(ann, cfgRef->learningRate, cfgRef->momentumCoef, errorStore);

	if(output != NULL)
		memcpy(output, outputStore, cfgRef->outputs * sizeof(double));

	if(err != NULL)
		memcpy(err, errorStore, cfgRef->outputs * sizeof(double));

RET:
	if(outputStore != NULL)
		free(outputStore);

	if(errorStore != NULL)
		free(errorStore);

	LOG("exit");
	return retValue;
}

