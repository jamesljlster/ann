#ifndef __ANN_H__
#define __ANN_H__

enum ANN_RETUEN_VALUE
{
	ANN_NO_ERROR		= 0,
	ANN_MEM_FAILED		= -1,
	ANN_FILE_FAILED		= -2,
	ANN_SYNTAX_ERROR	= -3,
	ANN_INFO_NOT_FOUND	= -4,
	ANN_OUT_OF_RANGE	= -5
};

enum ANN_TRANSFER_FUNC
{
	ANN_SIGMOID,
	ANN_MODIFIED_SIGMOID,
	ANN_HYPERBOLIC_TANGENT,
	ANN_GAUSSIAN,
	ANN_MODIFIED_GAUSSIAN
};

typedef void* ann_t;
typedef void* ann_config_t;

#ifdef __cplusplus
extern "C" {
#endif

//int ann_create_args(ann_t* annPtr, int inputs, int outputs, int hiddenLayers, ...);
int ann_create(ann_t* annPtr, ann_config_t config);
int ann_import(ann_t* annPtr, const char* filePath);
int ann_export(ann_t ann, const char* filePath);
void ann_delete(ann_t ann);
void ann_print(ann_t ann);

ann_config_t ann_get_config(ann_t ann);

int ann_set_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex, double value);
int ann_set_threshold(ann_t ann, int layerIndex, int nodeIndex, double value);
double ann_get_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex);
double ann_get_threshold(ann_t ann, int layerIndex, int nodeIndex);

//int ann_config_create(ann_config_t* configPtr, int inputs, int outputs, int tFuncIndex);
int ann_config_create(ann_config_t* configPtr);
int ann_config_import(ann_config_t* configPtr, const char* filePath);
int ann_config_export(ann_config_t config, const char* filePath);
void ann_config_delete(ann_config_t config);
void ann_config_print(ann_config_t config);

int ann_config_set_inputs(ann_config_t config, int inputs);
int ann_config_set_outputs(ann_config_t config, int outputs);
int ann_config_set_hidden_layers(ann_config_t config, int hiddenLayers);
int ann_config_set_hodden_nodes(ann_config_t config, int hiddenLayerIndex, int nodes);
int ann_config_set_transfer_func(ann_config_t config, int tFuncIndex);
int ann_config_set_learning_rate(ann_config_t config, double learningRate);
int ann_config_set_momentum_coef(ann_config_t config, double momentumCoef);

int ann_config_get_inputs(ann_config_t config);
int ann_config_get_outputs(ann_config_t config);
int ann_config_get_hidden_layers(ann_config_t config);
int ann_config_get_hidden_nodes(ann_config_t config, int hiddenLayerIndex);
int ann_config_get_transfer_func(ann_config_t config);
double ann_config_get_learning_rate(ann_config_t config);
double ann_config_get_momentum_coef(ann_config_t config);

int ann_training_gradient(ann_t ann, double* input, double* desire, double* output, double* err);
int ann_forward_computation(ann_t ann, double* input, double* output);
int ann_backpropagation(ann_t ann, double learningRate, double momentumCoef, double* dError);

#ifdef __cplusplus
}
#endif

#endif
