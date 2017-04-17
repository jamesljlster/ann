#include <stdlib.h>
#include <stdarg.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int ann_create_args(ann_t* annPtr, int inputs, int outputs, int tFuncIndex, double learningRate, double momentumCoef, int hiddenLayers, ...)
{
	int i;
	int iResult;
	int retValue = ANN_NO_ERROR;
	
	ann_t ann = NULL;
	ann_config_t cfg = NULL;

	int tmp;
	va_list argList;
	
	// Create config
	iResult = ann_config_create(&cfg);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Set config
	ann_config_set_inputs(cfg, inputs);
	ann_config_set_outputs(cfg, outputs);
	ann_config_set_transfer_func(cfg, tFuncIndex);
	ann_config_set_learning_rate(cfg, learningRate);
	ann_config_set_momentum_coef(cfg, momentumCoef);
	
	iResult = ann_config_set_hidden_layers(cfg, hiddenLayers);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	va_start(argList, hiddenLayers);
	for(i = 0; i < hiddenLayers; i++)
	{
		tmp = va_arg(argList, int);
		iResult = ann_config_set_hidden_nodes(cfg, i, tmp);
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto ERR;
		}
	}
	va_end(argList);

	// Create neural network
	iResult = ann_create(&ann, cfg);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Assign value
	*annPtr = ann;

	goto RET;

ERR:
	if(ann != NULL)
		ann_delete(ann);

RET:
	if(cfg != NULL)
		ann_config_delete(cfg);

	return retValue;
}

int ann_config_create_args(ann_config_t* configPtr, int inputs, int outputs, int tFuncIndex, double learningRate, double momentumCoef, int hiddenLayers, ...)
{
	int i;
	int iResult;
	int retValue = ANN_NO_ERROR;
	ann_config_t cfg = NULL;

	int tmp;
	va_list argList;
	
	// Create config
	iResult = ann_config_create(&cfg);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Set config
	ann_config_set_inputs(cfg, inputs);
	ann_config_set_outputs(cfg, outputs);
	ann_config_set_transfer_func(cfg, tFuncIndex);
	ann_config_set_learning_rate(cfg, learningRate);
	ann_config_set_momentum_coef(cfg, momentumCoef);
	
	iResult = ann_config_set_hidden_layers(cfg, hiddenLayers);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	va_start(argList, hiddenLayers);
	for(i = 0; i < hiddenLayers; i++)
	{
		tmp = va_arg(argList, int);
		iResult = ann_config_set_hidden_nodes(cfg, i, tmp);
		if(iResult != ANN_NO_ERROR)
		{
			retValue = iResult;
			goto ERR;
		}
	}
	va_end(argList);

	// Assign value
	*configPtr = cfg;

	goto RET;

ERR:
	if(cfg != NULL)
		ann_config_delete(cfg);

RET:
	return retValue;
}

int ann_config_create(ann_config_t* configPtr)
{
	struct ANN_CONFIG_STRUCT* cfgRef;
	
	cfgRef = malloc(sizeof(struct ANN_CONFIG_STRUCT));
	if(cfgRef == NULL)
	{
		return ANN_MEM_FAILED;
	}
	
	ann_config_zeromem(cfgRef);

	*configPtr = cfgRef;
	
	return ANN_NO_ERROR;
}

int ann_create(ann_t* annPtr, ann_config_t config)
{
	int iResult;
	int retValue = ANN_NO_ERROR;
	struct ANN_STRUCT* annRef = NULL;
	struct ANN_CONFIG_STRUCT* cfgRef = config;
	
	LOG("enter");

	// Memory allocation
	annRef = malloc(sizeof(struct ANN_STRUCT));
	if(annRef == NULL)
	{
		return ANN_MEM_FAILED;
	}
	else
	{
		ann_zeromem(annRef);
	}

	// Clone config
	iResult = ann_clone_config_struct(&annRef->config, cfgRef);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Create nerwork
	iResult = ann_allocate_network(annRef);
	if(iResult != ANN_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Assign value
	*annPtr = annRef;

	goto RET;

ERR:
	ann_delete_struct(annRef);

RET:
	LOG("exit");
	return retValue;
}
