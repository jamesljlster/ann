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
