#include <stdio.h>

#include "ann.h"
#include "ann_file_header.h"
#include "ann_private.h"
#include "ann_builtin_math.h"

#include "debug.h"

void ann_config_print(ann_config_t config)
{
	struct ANN_CONFIG_STRUCT* cfgRef = (struct ANN_CONFIG_STRUCT*)config;

	ann_config_print_struct(cfgRef);
}

void ann_fprint_weight(FILE* fptr, struct ANN_STRUCT* asPtr)
{
	int i, j, k;

	log("enter");

	fprintf(fptr, "[%s]\n", ann_file_header[ANN_HEADER_WEIGHT_FACTOR]);
	fprintf(fptr, "%s\n", ann_header_weight_factor[0]);
	for(i = 1; i < asPtr->config.layers; i++)
	{
		for(k = 0; k < asPtr->layerList[i - 1].nodeCount; k++)
		{
			for(j = 0; j < asPtr->layerList[i].nodeCount; j++)
			{
				fprintf(fptr, "%02d-%02d-%02d=%.32lf\n", i + 1, k + 1, j + 1, asPtr->layerList[i].nodeList[j].weight[k]);
			}
		}
	}
	fprintf(fptr, "\n");

	log("exit");
}

void ann_fprint_threshold(FILE* fptr, struct ANN_STRUCT* asPtr)
{
	int i, j;

	log("enter");

	fprintf(fptr, "[%s]\n", ann_file_header[ANN_HEADER_THRESHOLD_VALUE]);
	fprintf(fptr, "%s\n", ann_header_threshold_value[0]);
	for(i = 0; i < asPtr->config.layers; i++)
	{
		for(j = 0; j < asPtr->layerList[i].nodeCount; j++)
		{
			fprintf(fptr, "%02d-%02d=%.32lf\n", i + 1, j + 1, asPtr->layerList[i].nodeList[j].threshold);
		}	
	}
	fprintf(fptr, "\n"); 

	log("exit");
}

void ann_config_print_struct(struct ANN_CONFIG_STRUCT* cfgPtr)
{
	int i;
	
	log("enter");

	printf("[%s]\n", ann_file_header[ANN_HEADER_TOPOLOGY]);
	printf("%s= %d\n", ann_header_topology[ANN_HEADER_TOPOLOGY_INPUTS], cfgPtr->inputs);
	printf("%s= %d\n", ann_header_topology[ANN_HEADER_TOPOLOGY_OUTPUTS], cfgPtr->outputs);
	printf("%s= %d\n", ann_header_topology[ANN_HEADER_TOPOLOGY_LAYERS], cfgPtr->layers);
	printf("%s=%s\n", ann_header_topology[ANN_HEADER_TOPOLOGY_TRANSFER_FUNC], ann_transfer_func_name[cfgPtr->transferFuncIndex]);
	printf("\n");
	
	printf("[%s]\n", ann_file_header[ANN_HEADER_TRAINING_INFO]);
	printf("%s= %lf\n", ann_header_training_info[ANN_HEADER_TRAINING_INFO_LEARNING_RATE], cfgPtr->learningRate);
	printf("%s= %lf\n", ann_header_training_info[ANN_HEADER_TRAINING_INFO_MOMENTUM_COEF], cfgPtr->momentumCoef);
	printf("\n");

	printf("[%s]\n", ann_file_header[ANN_HEADER_TOTAL_NODE]);
	printf("%s\n", ann_header_total_node[0]);
	for(i = 1; i < cfgPtr->layers - 1; i++)
	{
		printf("%02d= %d\n", i + 1, cfgPtr->nodeList[i]);
	}
	printf("\n");

	log("exit");
}
