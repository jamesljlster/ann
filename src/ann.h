/**
 *	@author	Zheng-Ling Lai <jamesljlster@gmail.com>
 *	@file	ann.h
**/

#ifndef __ANN_H__
#define __ANN_H__

/** Return value definitions of ann library. */
enum ANN_RETUEN_VALUE
{
	ANN_NO_ERROR		= 0,	/*!< No error occured while running called function. */
	ANN_MEM_FAILED		= -1,	/*!< Memory allocation failed. */
	ANN_FILE_FAILED		= -2,	/*!< File processing failed. */
	ANN_SYNTAX_ERROR	= -3,	/*!< There is(are) syntax error(s) in file. */
	ANN_INFO_NOT_FOUND	= -4,	/*!< Important information(s) not found in file. */
	ANN_OUT_OF_RANGE	= -5	/*!< Processing out of range. */
};

/** Transfer (activation) function index definitions. */
enum ANN_TRANSFER_FUNC
{
	ANN_SIGMOID,				/*!< Sigmoid function. */
	ANN_MODIFIED_SIGMOID,		/*!< Modified sigmoid function. */
	ANN_HYPERBOLIC_TANGENT,		/*!< Hyperbolic tangent function. */
	ANN_GAUSSIAN,				/*!< Gaussian function. */
	ANN_MODIFIED_GAUSSIAN		/*!< Modified gaussian function. */
};

/** Type definition of ann. */
typedef void* ann_t;

/** Type definition of ann configuration. */
typedef void* ann_config_t;

#ifdef __cplusplus
extern "C" {
#endif

int ann_create_args(ann_t* annPtr, int inputs, int outputs, int tFuncIndex, double learningRate, double momentumCoef, int hiddenLayers, ...);
/**
 *	@fn		int ann_create_args(ann_t* annPtr, int inputs, int outputs, int tFuncIndex, double learningRate, double momentumCoef, int hiddenLayers, ...);
 *	@brief	Create neural network with function arguments. For more detail and example, please visit the wiki on git website.
 *	@param	annPtr:			Pointer of ann_t type variable.
 *	@param	inputs:			Inputs of neural network.
 *	@param	outputs:		Outputs of neural network.
 *	@param	tFuncIndex:		Transfer function index of neural network. Transfer function index is described by #ANN_TRANSFER_FUNC.
 *	@param	learningRate:	Learinig rate of neural network.
 *	@param	momentumCoef:	Momentum coefficient of neural network.
 *	@param	hiddenLayers:	Hidden layers of neural network.
 *	@param	... :			Nodes of each hidden layers in neural network.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 */

int ann_create(ann_t* annPtr, ann_config_t config);
/**
 *	@fn		int ann_create(ann_t* annPtr, ann_config_t config);
 *	@brief	Create neural network with ann configuration.
 *	@param	annPtr:	Pointer of ann_t type variable.
 *	@param	config:	Ann configuration.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 */

int ann_import(ann_t* annPtr, const char* filePath);
/**
 *	@fn		int ann_import(ann_t* annPtr, const char* filePath);
 *	@brief	Import neural network with given file path.
 *	@param	annPtr:		Pointer of ann_t type variable.
 *	@param	filePath:	Input file path of neural network file.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 */
 
int ann_export(ann_t ann, const char* filePath);
/**
 *	@fn		int ann_export(ann_t ann, const char* filePath);
 *	@brief	Export neural network with given file path.
 *	@param	ann:		ann_t type variable.
 *	@param	filePath:	Output file path of neural network file.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 */

int ann_clone(ann_t* dstAnnPtr, ann_t srcAnn);
/**
 *	@fn		int ann_clone(ann_t* dstAnnPtr, ann_t srcAnn);
 *	@brief	Clone neural network.
 *	@param	dstAnnPtr:	Pointer of destination ann_t type variable.
 *	@param	srcAnn:		Source ann_t type variable.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 */

void ann_delete(ann_t ann);
/**
 *	@fn		void ann_delete(ann_t ann);
 *	@brief	Delete neural network.
 *	@param	ann:	Target ann_t type variable.
 */

void ann_print(ann_t ann);
/**
 *	@fn		void ann_print(ann_t ann);
 *	@brief	Print target neural network.
 *	@param	ann:	Target ann_t type variable.
 */

ann_config_t ann_get_config(ann_t ann);
/**
 *	@fn		ann_config_t ann_get_config(ann_t ann);
 *	@brief	Get configuration form existed neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@return	Configuration of target neural network.
 */

int ann_set_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex, double value);
/**
 *	@fn		int ann_set_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex, double value);
 *	@brief	Set target weight of neural network.
 *	@param	ann:			Target ann_t type variable.
 *	@param	layerIndex:		Layer index of target weight.
 *	@param	preNodeIndex:	Node index of target weight that link to previous layer.
 *	@param	nodeIndex:		Node index of target weight thar link to current layer.
 *	@param	value:			Weight value.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 */

int ann_set_threshold(ann_t ann, int layerIndex, int nodeIndex, double value);
/**
 *	@fn		int ann_set_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex, double value);
 *	@brief	Set target threshold of neural network.
 *	@param	ann:			Target ann_t type variable.
 *	@param	layerIndex:		Layer index of target threshold.
 *	@param	nodeIndex:		Node index of target threshold thar link to current layer.
 *	@param	value:			Threshold value.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 */

void ann_zero_weight(ann_t ann);
/**
 *	@fn		void ann_zero_weight(ann_t ann);
 *	@brief	Zero all weight in neural network.
 *	@param	ann:	Target ann_t type variable.
 */

void ann_zero_threshold(ann_t ann);
/**
 *	@fn		void ann_zero_threshold(ann_t ann);
 *	@brief	Zero all threshold in neural network.
 *	@param	ann:	Target ann_t type variable.
 */

void ann_rand_weight(ann_t ann);
/**
 *	@fn		void ann_rand_weight(ann_t ann);
 *	@brief	Random all weight in neural network.
 *	@param	ann:	Target ann_t type variable.
 */

void ann_rand_threshold(ann_t ann);
/**
 *	@fn		void ann_rand_threshold(ann_t ann);
 *	@brief	Random all threshold in neural network.
 *	@param	ann:	Target ann_t type variable.
 */

double ann_get_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex);
/**
 *	@fn		double ann_get_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex);
 *	@brief	Get weight value with given information.
 *	@param	ann:			Target ann_t type variable.
 *	@param	layerIndex:		Layer index of target neural network node.
 *	@param	preNodeIndex:	The node index of the weight that link to previous layer.
 *	@param	nodeIndex:		The node index of the weight that link to current layer.
 *	@return	Target weight value.
 */

double ann_get_threshold(ann_t ann, int layerIndex, int nodeIndex);
/**
 *	@fn		double ann_get_threshold(ann_t ann, int layerIndex, int nodeIndex);
 *	@brief	Get threshold value with given information.
 *	@param	ann:		Target ann_t type variable.
 *	@param	layerIndex: Layer index of target neural network node.
 *	@param	nodeIndex:	The node index of the target neural network node.
 *	@return	Target threshold value.
 */

int ann_get_inputs(ann_t ann);
/**
 *	@fn		int ann_get_inputs(ann_t ann);
 *	@brief	Get inputs of target neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@return	Inputs of target neural network.
 */

int ann_get_outputs(ann_t ann);
/**
 *	@fn		int ann_get_outputs(ann_t ann);
 *	@brief	Get outputs of target neural network.
 *	@param	ann: Target ann_t type variable.
 *	@return	Outputs of target neural network.
 */

int ann_get_hidden_layers(ann_t ann);
/**
 *	@fn		int ann_get_hidden_layers(ann_t ann);
 *	@brief	Get hidden layers of target neural network.
 *	@param	ann: Target ann_t type variable.
 *	@return	Outputs of target neural network.
 */

int ann_get_hidden_nodes(ann_t ann, int hiddenLayerIndex);
/**
 *	@fn		int ann_get_hidden_nodes(ann_t ann, int hiddenLayerIndex);
 *	@brief	Get hidden nodes of target hidden layer.
 *	@param	ann:				Target ann_t type variable.
 *	@param	hiddenLayerIndex:	Target hidden layer index of neural network.
 *	@return	Hidden nodes of target hidden layer in neural network.
 */

int ann_get_transfer_func(ann_t ann);
/**
 *	@fn		int ann_get_transfer_func(ann_t ann);
 *	@brief	Get transfer (activation) function index of target neural network.
 *	@param	ann: Target ann_t type variable.
 *	@return Transfer (activation) function index of target neural network. Transfer function index is described by #ANN_TRANSFER_FUNC.
 */

double ann_get_learning_rate(ann_t ann);
/**
 *	@fn		double ann_get_learning_rate(ann_t ann);
 *	@brief	Get default learning rate of target neural network.
 *	@param	ann: Target ann_t type variable.
 *	@return	Default learning rate of neural network.
 */

double ann_get_momentum_coef(ann_t ann);

int ann_config_create_args(ann_config_t* configPtr, int inputs, int outputs, int tFuncIndex, double learningRate, double momentumCoef, int hiddenLayers, ...);
int ann_config_create(ann_config_t* configPtr);
int ann_config_import(ann_config_t* configPtr, const char* filePath);
int ann_config_export(ann_config_t config, const char* filePath);
void ann_config_delete(ann_config_t config);
void ann_config_print(ann_config_t config);

int ann_config_set_hidden_layers(ann_config_t config, int hiddenLayers);
int ann_config_set_hidden_nodes(ann_config_t config, int hiddenLayerIndex, int nodes);
void ann_config_set_inputs(ann_config_t config, int inputs);
void ann_config_set_outputs(ann_config_t config, int outputs);
void ann_config_set_transfer_func(ann_config_t config, int tFuncIndex);
void ann_config_set_learning_rate(ann_config_t config, double learningRate);
void ann_config_set_momentum_coef(ann_config_t config, double momentumCoef);

int ann_config_get_inputs(ann_config_t config);
int ann_config_get_outputs(ann_config_t config);
int ann_config_get_hidden_layers(ann_config_t config);
int ann_config_get_hidden_nodes(ann_config_t config, int hiddenLayerIndex);
int ann_config_get_transfer_func(ann_config_t config);
double ann_config_get_learning_rate(ann_config_t config);
double ann_config_get_momentum_coef(ann_config_t config);

int ann_training_gradient(ann_t ann, double* input, double* desire, double* output, double* err);
int ann_training_gradient_custom(ann_t ann, double learningRate, double momentumCoef, double* input, double* desire, double* output, double* err);
void ann_forward_computation(ann_t ann, double* input, double* output);
void ann_backpropagation(ann_t ann, double learningRate, double momentumCoef, double* dError);

#ifdef __cplusplus
}
#endif

#endif
