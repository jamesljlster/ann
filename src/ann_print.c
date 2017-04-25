#include <stdio.h>

#include "ann.h"
#include "ann_print.h"
#include "ann_file_header.h"
#include "ann_private.h"
#include "ann_builtin_math.h"

#include "debug.h"

void ann_fprint_topology(FILE* fptr, struct ANN_CONFIG_STRUCT* cfgPtr);
void ann_fprint_training_info(FILE* fptr, struct ANN_CONFIG_STRUCT* cfgPtr);
void ann_fprint_total_node(FILE* fptr, struct ANN_CONFIG_STRUCT* cfgPtr);

void ann_fprint_header(FILE* fptr)
{
	fprintf(fptr, "[%s]\n", ann_file_header[ANN_HEADER_APPLICATION_MSG]);
	fprintf(fptr, "%s\n", ann_header_application[0]);
	fprintf(fptr, "\n");
}

void ann_print(ann_t ann)
{
	struct ANN_STRUCT* annRef = ann;

	ann_fprint_config(stdout, &annRef->config);
	ann_fprint_threshold(stdout, annRef);
	ann_fprint_weight(stdout, annRef);
	ann_fprint_recurrent_weight(stdout, annRef);
}

void ann_config_print(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgRef = (struct ANN_CONFIG_STRUCT*)config;
	
	ann_fprint_config(stdout, cfgRef);
}

void ann_fprint_weight(FILE* fptr, struct ANN_STRUCT* asPtr)
{
	int i, j, k;

	LOG("enter");

	fprintf(fptr, "[%s]\n", ann_file_header[ANN_HEADER_WEIGHT_FACTOR]);
	fprintf(fptr, "%s\n", ann_header_weight_factor[0]);
	for(i = 1; i < asPtr->config.layers; i++)
	{
		for(k = 0; k < asPtr->layerList[i - 1].nodeCount; k++)
		{
			for(j = 0; j < asPtr->layerList[i].nodeCount; j++)
			{
				fprintf(fptr, "%02d-%02d-%02d=%.32G\n", i + 1, k + 1, j + 1, asPtr->layerList[i].nodeList[j].weight[k]);
			}
		}
	}
	fprintf(fptr, "\n");

	LOG("exit");
}

void ann_fprint_recurrent_weight(FILE* fptr, struct ANN_STRUCT* asPtr)
{
	int i, j;
	struct ANN_LAYER* preLayerRef;
	struct ANN_LAYER* layerRef;
	int layers;

	LOG("enter");

	layers = asPtr->config.layers;
	if(layers > 2)
	{
		fprintf(fptr, "[%s]\n", ann_file_header[ANN_HEADER_RECURRENT_WEIGHT]);
		fprintf(fptr, "%s\n", ann_header_recurrent_weight[0]);

		// Set layer reference
		preLayerRef = &asPtr->layerList[layers - 2];
		layerRef = &asPtr->layerList[1];

		for(i = 0; i < preLayerRef->nodeCount; i++)
		{
			for(j = 0; j < layerRef->nodeCount; j++)
			{
				fprintf(fptr, "%02d-%02d=%.32G\n", i + 1, j + 1, layerRef->nodeList[j].rWeight[i]);
			}
		}
	}
}

void ann_fprint_threshold(FILE* fptr, struct ANN_STRUCT* asPtr)
{
	int i, j;

	LOG("enter");

	fprintf(fptr, "[%s]\n", ann_file_header[ANN_HEADER_THRESHOLD_VALUE]);
	fprintf(fptr, "%s\n", ann_header_threshold_value[0]);
	for(i = 0; i < asPtr->config.layers; i++)
	{
		for(j = 0; j < asPtr->layerList[i].nodeCount; j++)
		{
			fprintf(fptr, "%02d-%02d=%.32G\n", i + 1, j + 1, asPtr->layerList[i].nodeList[j].threshold);
		}	
	}
	fprintf(fptr, "\n"); 

	LOG("exit");
}

void ann_fprint_config(FILE* fptr, struct ANN_CONFIG_STRUCT* cfgPtr)
{
	LOG("enter");
	
	ann_fprint_topology(fptr, cfgPtr);
	ann_fprint_training_info(fptr, cfgPtr);
	ann_fprint_total_node(fptr, cfgPtr);

	LOG("exit");
}

void ann_fprint_topology(FILE* fptr, struct ANN_CONFIG_STRUCT* cfgPtr)
{
	LOG("enter");

	fprintf(fptr, "[%s]\n", ann_file_header[ANN_HEADER_TOPOLOGY]);
	fprintf(fptr, "%s= %d\n", ann_header_topology[ANN_HEADER_TOPOLOGY_INPUTS], cfgPtr->inputs);
	fprintf(fptr, "%s= %d\n", ann_header_topology[ANN_HEADER_TOPOLOGY_OUTPUTS], cfgPtr->outputs);
	fprintf(fptr, "%s= %d\n", ann_header_topology[ANN_HEADER_TOPOLOGY_LAYERS], cfgPtr->layers);
	fprintf(fptr, "%s=%s\n", ann_header_topology[ANN_HEADER_TOPOLOGY_TRANSFER_FUNC], ann_transfer_func_name[cfgPtr->transferFuncIndex]);
	fprintf(fptr, "\n");

	LOG("exit");
}

void ann_fprint_training_info(FILE* fptr, struct ANN_CONFIG_STRUCT* cfgPtr)
{
	LOG("enter");

	fprintf(fptr, "[%s]\n", ann_file_header[ANN_HEADER_TRAINING_INFO]);
	fprintf(fptr, "%s= %G\n", ann_header_training_info[ANN_HEADER_TRAINING_INFO_LEARNING_RATE], cfgPtr->learningRate);
	fprintf(fptr, "%s= %G\n", ann_header_training_info[ANN_HEADER_TRAINING_INFO_MOMENTUM_COEF], cfgPtr->momentumCoef);
	fprintf(fptr, "\n");

	LOG("exit");
}

void ann_fprint_total_node(FILE* fptr, struct ANN_CONFIG_STRUCT* cfgPtr)
{
	int i;

	LOG("enter");

	fprintf(fptr, "[%s]\n", ann_file_header[ANN_HEADER_TOTAL_NODE]);
	fprintf(fptr, "%s\n", ann_header_total_node[0]);
	if(cfgPtr->nodeList != NULL)
	{
		for(i = 1; i < cfgPtr->layers - 1; i++)
		{
			fprintf(fptr, "%02d= %d\n", i + 1, cfgPtr->nodeList[i]);
		}
	}
	fprintf(fptr, "\n");

	LOG("exit");
}

