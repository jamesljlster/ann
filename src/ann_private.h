#ifndef __ANN_PRIVATE_H__
#define __ANN_PRIVATE_H__

#include <stdio.h>
#include "ann_file_proc.h"

struct ANN_NODE
{
	double* weight;
	double* deltaW;

	double threshold;
	double deltaTh;

	double sCalc;
	double output;
};

struct ANN_LAYER
{
    double (*activeFunc)(double);
    double (*dActiveFunc)(double);

    struct ANN_NODE* nodeList;
    int nodeCount;
};

struct ANN_CONFIG_STRUCT
{
	int inputs;
	int outputs;
	int layers;	
	int transferFuncIndex;
	
	double learningRate;
	double momentumCoef;

	int* nodeList;
};

struct ANN_STRUCT
{
    struct ANN_LAYER* layerList;

	struct ANN_CONFIG_STRUCT config;
};

#ifdef __cplusplus
extern "C" {
#endif

int ann_clone_config(struct ANN_CONFIG_STRUCT* dst, struct ANN_CONFIG_STRUCT* src);

int ann_allocate_network(struct ANN_STRUCT* sptr);

int ann_parse_config(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_STRUCT* fsPtr);
int ann_parse_network(struct ANN_STRUCT* asPtr, struct ANN_FILE_STRUCT* fsPtr);

void ann_fprint_header(FILE* fptr);
void ann_fprint_config(FILE* fptr, struct ANN_CONFIG_STRUCT* cfgPtr);
void ann_fprint_threshold(FILE* fptr, struct ANN_STRUCT* asPtr);
void ann_fprint_weight(FILE* fptr, struct ANN_STRUCT* asPtr);

void ann_zeromem(struct ANN_STRUCT* asPtr);
void ann_config_zeromem(struct ANN_CONFIG_STRUCT* cfgPtr);

void ann_config_print_struct(struct ANN_CONFIG_STRUCT* cfgPtr);

void ann_config_delete_struct(struct ANN_CONFIG_STRUCT* cfgPtr);

void ann_delete_node(struct ANN_NODE* nodePtr);
void ann_delete_layer(struct ANN_LAYER* layerPtr);
void ann_delete_struct(struct ANN_STRUCT* structPtr);

int ann_set_weight_struct(struct ANN_STRUCT* sptr, int layerIndex, int preNodeIndex, int nodeIndex, double value);
int ann_set_threshold_struct(struct ANN_STRUCT* sptr, int layerIndex, int nodeIndex, double value);

#ifdef __cplusplus
}
#endif

#endif
