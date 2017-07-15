/**
 *	@author	Zheng-Ling Lai <jamesljlster@gmail.com>
 *	@file	ann.h
**/

#ifndef __ANN_H__
#define __ANN_H__

/** Return value definitions of ann library. */
enum ANN_RETUEN_VALUE
{
	ANN_NO_ERROR		= 0,	/*!< No error occured while running called function. @since 0.1.0 */
	ANN_MEM_FAILED		= -1,	/*!< Memory allocation failed. @since 0.1.0 */
	ANN_FILE_FAILED		= -2,	/*!< File processing failed. @since 0.1.0 */
	ANN_SYNTAX_ERROR	= -3,	/*!< There is(are) syntax error(s) in file. @since 0.1.0 */
	ANN_INFO_NOT_FOUND	= -4,	/*!< Important information(s) not found in file. @since 0.1.0 */
	ANN_OUT_OF_RANGE	= -5,	/*!< Processing out of range. @since 0.1.0 */
	ANN_INVALID_ARG		= -6	/*!< Invalid argument(s) or setting(s). @since 0.2.2 */
};

/** Transfer (activation) function index definitions. */
enum ANN_TRANSFER_FUNC
{
	ANN_SIGMOID				= 0,	/*!< Sigmoid function. @since 0.1.0 */
	ANN_MODIFIED_SIGMOID	= 1,	/*!< Modified sigmoid function. @since 0.1.2 */
	ANN_HYPERBOLIC_TANGENT	= 2,	/*!< Hyperbolic tangent function. @since 0.1.2 */
	ANN_GAUSSIAN			= 3,	/*!< Gaussian function. @since 0.1.3 */
	ANN_MODIFIED_GAUSSIAN	= 4,	/*!< Modified gaussian function. @since 0.1.3 */
	ANN_BENT_IDENTITY		= 5,	/*!< Bent identity function. @since 0.2.2 */
	ANN_SOFTPLUS			= 6,	/*!< SoftPlus function. @since 0.2.2 */
	ANN_SOFTSIGN			= 7,	/*!< SoftSign function. @since 0.2.2 */
	ANN_SINC				= 8,	/*!< Sinc function. @since 0.2.2 */
	ANN_SINUSOID			= 9,	/*!< Sinusoid (sine) function. @since 0.2.2 */
	ANN_IDENTITY			= 10,	/*!< Identity function. @since 0.2.2 */
	ANN_RELU				= 11	/*!< Rectifier linear unit function. @since 0.2.2 */
};

/** Type definition of ann. @since 0.2.0 */
typedef struct ANN_STRUCT* ann_t;

/** Type definition of ann configuration. @since 0.2.0 */
typedef struct ANN_CONFIG_STRUCT* ann_config_t;

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
 *	@param	...:			Nodes of each hidden layers in neural network.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

int ann_create(ann_t* annPtr, ann_config_t config);
/**
 *	@fn		int ann_create(ann_t* annPtr, ann_config_t config);
 *	@brief	Create neural network with ann configuration.
 *	@param	annPtr:	Pointer of ann_t type variable.
 *	@param	config:	Ann configuration.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

int ann_import(ann_t* annPtr, const char* filePath);
/**
 *	@fn		int ann_import(ann_t* annPtr, const char* filePath);
 *	@brief	Import neural network with given file path.
 *	@param	annPtr:		Pointer of ann_t type variable.
 *	@param	filePath:	Input file path of neural network file.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */
 
int ann_export(ann_t ann, const char* filePath);
/**
 *	@fn		int ann_export(ann_t ann, const char* filePath);
 *	@brief	Export neural network with given file path.
 *	@param	ann:		ann_t type variable.
 *	@param	filePath:	Output file path of neural network file.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

int ann_clone(ann_t* dstAnnPtr, ann_t srcAnn);
/**
 *	@fn		int ann_clone(ann_t* dstAnnPtr, ann_t srcAnn);
 *	@brief	Clone neural network.
 *	@param	dstAnnPtr:	Pointer of destination ann_t type variable.
 *	@param	srcAnn:		Source ann_t type variable.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.4
 */

int ann_config_clone(ann_config_t* dstCfgPtr, ann_config_t srcCfg);
/**
 *	@fn		int ann_config_clone(ann_config_t* dstCfgPtr, ann_config_t srcCfg);
 *	@brief	Clone neural network configuration.
 *	@param	dstCfgPtr:	Pointer of destination ann_config_t type variable.
 *	@param	srcCfg:		Source ann_config_t type variable.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.2.4
 */

void ann_delete(ann_t ann);
/**
 *	@fn		void ann_delete(ann_t ann);
 *	@brief	Delete neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@since	0.1.0
 */

void ann_print(ann_t ann);
/**
 *	@fn		void ann_print(ann_t ann);
 *	@brief	Print target neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@since	0.1.0
 */

ann_config_t ann_get_config(ann_t ann);
/**
 *	@fn		ann_config_t ann_get_config(ann_t ann);
 *	@brief	Get configuration form existed neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@return	Configuration of target neural network.
 *	@since	0.1.0
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
 *	@since	0.1.0
 */

int ann_set_threshold(ann_t ann, int layerIndex, int nodeIndex, double value);
/**
 *	@fn		int ann_set_threshold(ann_t ann, int layerIndex, int nodeIndex, double value);
 *	@brief	Set target threshold of neural network.
 *	@param	ann:			Target ann_t type variable.
 *	@param	layerIndex:		Layer index of target threshold.
 *	@param	nodeIndex:		Node index of target threshold thar link to current layer.
 *	@param	value:			Threshold value.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

void ann_set_learning_rate(ann_t ann, double learningRate);
/**
 *	@fn		void ann_set_learning_rate(ann_t ann, double learningRate);
 *	@brief	Set default learning rate of target neural network.
 *	@param	ann:			Target ann_t variable.
 *	@param	learningRate:	Default learning rate of target neural network configuration.
 *	@since	0.2.5
 */

void ann_set_momentum_coef(ann_t ann, double momentumCoef);
/**
 *	@fn		void ann_set_momentum_coef(ann_t ann, double momentumCoef);
 *	@brief	Set default momentum coefficient of target neural network.
 *	@param	ann:			Target ann_t variable.
 *	@param	momentumCoef:	Default momentum coefficient of target neural network configuration.
 *	@since	0.2.5
 */

void ann_zero_weight(ann_t ann);
/**
 *	@fn		void ann_zero_weight(ann_t ann);
 *	@brief	Zero all weight in neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@since	0.1.0
 */

void ann_zero_threshold(ann_t ann);
/**
 *	@fn		void ann_zero_threshold(ann_t ann);
 *	@brief	Zero all threshold in neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@since	0.1.0
 */

void ann_rand_weight(ann_t ann);
/**
 *	@fn		void ann_rand_weight(ann_t ann);
 *	@brief	Random all weight in neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@since	0.1.0
 */

void ann_rand_recurrent_weight(ann_t ann);
/**
 *	@fn		void ann_rand_recurrent_weight(ann_t ann);
 *	@brief	Random all recurrent weight in neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@since	1.0.0
 */

void ann_rand_threshold(ann_t ann);
/**
 *	@fn		void ann_rand_threshold(ann_t ann);
 *	@brief	Random all threshold in neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@since	0.1.0
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
 *	@since	0.1.0
 */

double ann_get_threshold(ann_t ann, int layerIndex, int nodeIndex);
/**
 *	@fn		double ann_get_threshold(ann_t ann, int layerIndex, int nodeIndex);
 *	@brief	Get threshold value with given information.
 *	@param	ann:		Target ann_t type variable.
 *	@param	layerIndex: Layer index of target neural network node.
 *	@param	nodeIndex:	The node index of the target neural network node.
 *	@return	Target threshold value.
 *	@since	0.1.0
 */

int ann_get_inputs(ann_t ann);
/**
 *	@fn		int ann_get_inputs(ann_t ann);
 *	@brief	Get inputs of target neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@return	Inputs of target neural network.
 *	@since	0.1.0
 */

int ann_get_outputs(ann_t ann);
/**
 *	@fn		int ann_get_outputs(ann_t ann);
 *	@brief	Get outputs of target neural network.
 *	@param	ann: Target ann_t type variable.
 *	@return	Outputs of target neural network.
 *	@since	0.1.0
 */

int ann_get_hidden_layers(ann_t ann);
/**
 *	@fn		int ann_get_hidden_layers(ann_t ann);
 *	@brief	Get hidden layers of target neural network.
 *	@param	ann: Target ann_t type variable.
 *	@return	Hidden layers of target neural network.
 *	@since	0.1.0
 */

int ann_get_hidden_nodes(ann_t ann, int hiddenLayerIndex);
/**
 *	@fn		int ann_get_hidden_nodes(ann_t ann, int hiddenLayerIndex);
 *	@brief	Get hidden nodes of target hidden layer.
 *	@param	ann:				Target ann_t type variable.
 *	@param	hiddenLayerIndex:	Target hidden layer index of neural network.
 *	@return	Hidden nodes of target hidden layer in neural network.
 *	@since	0.1.0
 */

int ann_get_transfer_func(ann_t ann);
/**
 *	@fn		int ann_get_transfer_func(ann_t ann);
 *	@brief	Get transfer (activation) function index of target neural network.
 *	@param	ann: Target ann_t type variable.
 *	@return Transfer (activation) function index of target neural network. Transfer function index is described by #ANN_TRANSFER_FUNC.
 *	@since	0.1.0
 */

const char* ann_get_transfer_func_name(int tFuncIndex);
/**
 *	@fn		const char* ann_get_transfer_func_name(int tFuncIndex);
 *	@brief	Get the name of transfer (activation) function.
 *	@param	tFuncIndex:	Transfer (activation) function index of target neural network configuration.
 *	@return Constant string pointer of the transfer function name. The function would return NULL if tFuncIndex is out of range.
 *	@since	0.2.5
 */

int ann_get_transfer_func_id(char* tFuncName);
/**
 *	@fn		int ann_get_transfer_func_id(char* tFuncName);
 *	@brief	Get transfer function id with given transfer function name.
 *	@param	tFuncName: Transfer (activeation) function name.
 *	@return	ID of the transfer funciton. The function would return #ANN_INFO_NOT_FOUND if no any transfer function was corresponding with the given name.
 *	@since	1.0.0
 */

double ann_get_learning_rate(ann_t ann);
/**
 *	@fn		double ann_get_learning_rate(ann_t ann);
 *	@brief	Get default learning rate of target neural network.
 *	@param	ann: Target ann_t type variable.
 *	@return	Default learning rate of neural network.
 *	@since	0.1.0
 */

double ann_get_momentum_coef(ann_t ann);
/**
 *	@fn		double ann_get_momentum_coef(ann_t ann);
 *	@brief	Get default momentum coefficient of target neural network.
 *	@param	ann: Target ann_t type variable.
 *	@return Default momentum coefficient of neural network.
 *	@since	0.1.0
 */

int ann_config_create_args(ann_config_t* configPtr, int inputs, int outputs, int tFuncIndex, double learningRate, double momentumCoef, int hiddenLayers, ...);
/**
 *	@fn		int ann_config_create_args(ann_config_t* configPtr, int inputs, int outputs, int tFuncIndex, double learningRate, double momentumCoef, int hiddenLayers, ...);
 *	@brief	Create a neural network configuration with function arguments. For more detail and example, please visit the wiki on git website.
 *	@param	configPtr:		Pointer of ann_config_t type variable.
 *	@param	inputs:			Inputs of neural network.
 *	@param	outputs:		Outputs of neural network.
 *	@param	tFuncIndex:		Transfer function index of neural network. Transfer function index is described by #ANN_TRANSFER_FUNC.
 *	@param	learningRate:	Learinig rate of neural network.
 *	@param	momentumCoef:	Momentum coefficient of neural network.
 *	@param	hiddenLayers:	Hidden layers of neural network.
 *	@param	...:			Nodes of each hidden layers in neural network.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

int ann_config_create(ann_config_t* configPtr);
/**
 *	@fn		int ann_config_create(ann_config_t* configPtr);
 *	@brief	Create a empty neural network configuration.
 *	@param	configPtr:	Pointer of ann_config_t type.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

int ann_config_import(ann_config_t* configPtr, const char* filePath);
/**
 *	@fn		int ann_config_import(ann_config_t* configPtr, const char* filePath);
 *	@brief	Import neural network configuration with given file path.
 *	@param	configPtr:	Pointer of ann_config_t type variable.
 *	@param	filePath:	Input file path of neural network configuration file.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */
 
int ann_config_export(ann_config_t config, const char* filePath);
/**
 *	@fn		int ann_config_export(ann_config_t config, const char* filePath);
 *	@brief	Export neural network configuration with given file path.
 *	@param	config:		Target ann_config_t type variable.
 *	@param	filePath:	Output file path of neural network configuration file.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

void ann_config_delete(ann_config_t config);
/**
 *	@fn		void ann_config_delete(ann_config_t config);
 *	@brief	Delete neural network configuration.
 *	@param	config:	Target ann_config_t type variable.
 *	@since	0.1.0
 */

void ann_config_print(ann_config_t config);
/**
 *	@fn		void ann_config_print(ann_config_t config);
 *	@brief	Print target neural network configuration.
 *	@param	config:	Target ann_config_t type variable.
 *	@since	0.1.0
 */

int ann_config_set_hidden_layers(ann_config_t config, int hiddenLayers);
/**
 *	@fn		int ann_config_set_hidden_layers(ann_config_t config, int hiddenLayers);
 *	@brief	Set hidden layers of target neural network configuration.
 *	@param	config: 		Target ann_config_t type variable.
 *	@param	hiddenLayers:	Hidden layers of target neural network configuration.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

int ann_config_set_hidden_nodes(ann_config_t config, int hiddenLayerIndex, int nodes);
/**
 *	@fn		int ann_config_set_hidden_nodes(ann_config_t config, int hiddenLayerIndex, int nodes);
 *	@brief	Set nodes of target hidden layer in neural network configuration.
 *	@param	config:				Target ann_config_t variables.
 *	@param	hiddenLayerIndex:	Target hidden layer index in neural networl configuration.
 *	@param	nodes:				Nodes of target hidden layer.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

int ann_config_set_inputs(ann_config_t config, int inputs);
/**
 *	@fn		int ann_config_set_inputs(ann_config_t config, int inputs);
 *	@brief	Set inputs of target neural network configuration.
 *	@param	config:	Target ann_config_t variable.
 *	@param	inputs:	Inputs of target neural network configuration.
 *	@return If argument less then or equal with zero, the function would return #ANN_INVALID_ARG, else return #ANN_NO_ERROR.
 *	@since	0.1.0
 */

int ann_config_set_outputs(ann_config_t config, int outputs);
/**
 *	@fn		int ann_config_set_outputs(ann_config_t config, int outputs);
 *	@brief	Set outputs of target neural network configuration.
 *	@param	config:		Target ann_config_t variable.
 *	@param	outputs:	Outputs of target neural network configuration.
 *	@return If argument less then or equal with zero, the function would return #ANN_INVALID_ARG, else return #ANN_NO_ERROR.
 *	@since	0.1.0
 */

int ann_config_set_transfer_func(ann_config_t config, int tFuncIndex);
/**
 *	@fn		int ann_config_set_transfer_func(ann_config_t config, int tFuncIndex);
 *	@brief	Set transfer (activation) function index of target neural network configuration.
 *	@param	config:		Target ann_config_t variable.
 *	@param	tFuncIndex:	Transfer (activation) function index of target neural network configuration.
 *	@return If argument less then zero or greater then the highest transfer function index, the function would return #ANN_INVALID_ARG, else return #ANN_NO_ERROR.
 *	@since	0.1.0
 */

void ann_config_set_learning_rate(ann_config_t config, double learningRate);
/**
 *	@fn		void ann_config_set_learning_rate(ann_config_t config, double learningRate);
 *	@brief	Set default learning rate of target neural network configuration.
 *	@param	config:			Target ann_config_t variable.
 *	@param	learningRate:	Default learning rate of target neural network configuration.
 *	@since	0.1.0
 */

void ann_config_set_momentum_coef(ann_config_t config, double momentumCoef);
/**
 *	@fn		void ann_config_set_momentum_coef(ann_config_t config, double momentumCoef);
 *	@brief	Set default momentum coefficient of target neural network configuration.
 *	@param	config:			Target ann_config_t variable.
 *	@param	momentumCoef:	Default momentum coefficient of target neural network configuration.
 *	@since	0.1.0
 */

int ann_config_get_inputs(ann_config_t config);
/**
 *	@fn		int ann_config_get_inputs(ann_config_t config);
 *	@brief	Get inputs of target neural network configuration.
 *	@param	config:	Target ann_config_t type variable.
 *	@return	Inputs of target neural network configuration.
 *	@since	0.1.0
 */

int ann_config_get_outputs(ann_config_t config);
/**
 *	@fn		int ann_config_get_outputs(ann_config_t config);
 *	@brief	Get outputs of target neural network confuguration.
 *	@param	config:	Target ann_config_t type variable.
 *	@return	Outputs of target neural network configuration.
 *	@since	0.1.0
 */

int ann_config_get_hidden_layers(ann_config_t config);
/**
 *	@fn		int ann_config_get_hidden_layers(ann_config_t config);
 *	@brief	Get hidden layers of target neural network configuration.
 *	@param	config:	Target ann_config_t type variable.
 *	@return	Hidden layers of target neural network.
 *	@since	0.1.0
 */

int ann_config_get_hidden_nodes(ann_config_t config, int hiddenLayerIndex);
/**
 *	@fn		int ann_config_get_hidden_nodes(ann_config_t config, int hiddenLayerIndex);
 *	@brief	Get hidden nodes of target hidden layer in target neural network configuration.
 *	@param	config:				Target ann_config_t type variable.
 *	@param	hiddenLayerIndex:	Target hidden layer index of neural network.
 *	@return	Hidden nodes of target hidden layer in neural network configuration.
 *	@since	0.1.0
 */

int ann_config_get_transfer_func(ann_config_t config);
/**
 *	@fn		int ann_config_get_transfer_func(ann_config_t config);
 *	@brief	Get transfer (activation) function index of target neural network configuration.
 *	@param	config:	Target ann_config_t type variable.
 *	@return Transfer (activation) function index of target neural network configuration. Transfer function index is described by #ANN_TRANSFER_FUNC.
 *	@since	0.1.0
 */

double ann_config_get_learning_rate(ann_config_t config);
/**
 *	@fn		double ann_config_get_learning_rate(ann_config_t config);
 *	@brief	Get default learning rate of target neural network configuration.
 *	@param	config:	Target ann_config_t type variable.
 *	@return	Default learning rate of neural network configuration.
 *	@since	0.1.0
 */

double ann_config_get_momentum_coef(ann_config_t config);
/**
 *	@fn		double ann_config_get_momentum_coef(ann_config_t config);
 *	@brief	Get default momentum coefficient of target neural network configuration.
 *	@param	config:	Target ann_config_t type variable.
 *	@return Default momentum coefficient of neural network configuration.
 *	@since	0.1.0
 */

void ann_clear_momentum(ann_t ann);
/**
 *	@fn		void ann_clear_momentum(ann_t ann);
 *	@brief	Clear momentum in target neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@since	0.2.5
 */

int ann_training_gradient(ann_t ann, double* input, double* desire, double* output, double* err);
/**
 *	@fn		int ann_training_gradient(ann_t ann, double* input, double* desire, double* output, double* err);
 *	@brief	Processing neural network training.
 *	@param	ann:	Target ann_t type variable.
 *	@param	input:	Input array.
 *	@param	desire:	Desire output array.
 *	@param	output:	Array for storing outputs of forward computation. Pass NULL if you want to ignore it.
 *	@param	err:	Array for storing error (desire - output) before backpropagation. Pass NULL if you want to ignore it.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

int ann_training_gradient_custom(ann_t ann, double learningRate, double momentumCoef, double* input, double* desire, double* output, double* err);
/**
 *	@fn		int ann_training_gradient_custom(ann_t ann, double learningRate, double momentumCoef, double* input, double* desire, double* output, double* err);
 *	@brief	Processing neural network training with custom training settings.
 *	@param	ann:			Target ann_t type variable.
 *	@param	learningRate:	Custom learning rate.
 *	@param	momentumCoef:	Custom momentum coefficient.
 *	@param	input:			Input array.
 *	@param	desire:			Desire output array.
 *	@param	output:			Array for storing outputs of forward computation. Pass NULL if you want to ignore it.
 *	@param	err:			Array for storing error (desire - output) before backpropagation. Pass NULL if you want to ignore it.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.4
 */

void ann_forward_computation(ann_t ann, double* input, double* output);
/**
 *	@fn		void ann_forward_computation(ann_t ann, double* input, double* output);
 *	@brief	Processing neural network forward computation.
 *	@param	ann:	Target ann_t type variable.
 *	@param	input:	Input array.
 *	@param	output:	Array for storing outputs.
 *	@since	0.1.0
 */

void ann_backpropagation(ann_t ann, double learningRate, double momentumCoef, double* dError);
/**
 *	@fn		void ann_backpropagation(ann_t ann, double learningRate, double momentumCoef, double* dError);
 *	@brief	Processing neural network backpropagation.
 *	@param	ann:			Target ann_t type variable.
 *	@param	learningRate:	Custom learning rate in backpropagation.
 *	@param	momentumCoef:	Custom momentum coefficient in backpropagation.
 *	@param	dError:			Differential value of error value in cost function.
 *	@since	0.1.0
 */

const char* ann_get_error_msg(int retValue);
/**
 *	@fn		const char* ann_get_error_msg(int retValue);
 *	@brief	Get error msg with return value.
 *	@param	retValue:	Target return value that trying to parsing.
 *	@return Constant string pointer that contains parsing message.
 *	@since	0.2.0
 */

int rnn_training_gradient(ann_t ann, double** inputList, double** desireList, double** outputList, double** errList, int timeStep, double gradLimit);
/**
 *	@fn		int rnn_training_gradient(ann_t ann, double** inputList, double** desireList, double** outputList, double** errList, int timeStep, double gradLimit);
 *	@brief	Processing recurrent neural network training.
 *	@param	ann:		Target ann_t type variable.
 *	@param	inputList:	Array of Input array.
 *	@param	desireList:	Array of desire output array.
 *	@param	outputList:	Array of array for storing outputs of forward computation. Pass NULL if you want to ignore it.
 *	@param	errList:	Array of array for storing error (desire - output) before backpropagation. Pass NULL if you want to ignore it.
 *	@param	timeStep:	Time step of recurrent training.
 *	@param	gradLimit:	Gradient limit for recurrent training.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

int rnn_training_gradient_custom(ann_t ann, double learningRate, double momentumCoef, double** inputList, double** desireList, double** outputList, double** errList, int timeStep, double gradLimit);
/**
 *	@fn		int rnn_training_gradient_custom(ann_t ann, double learningRate, double momentumCoef, double** inputList, double** desireList, double** outputList, double** errList, int timeStep, double gradLimit);
 *	@brief	Processing recurrent neural network training.
 *	@param	ann:		Target ann_t type variable.
 *	@param	learningRate:	Custom learning rate.
 *	@param	momentumCoef:	Custom momentum coefficient.
 *	@param	inputList:	Array of Input array.
 *	@param	desireList:	Array of desire output array.
 *	@param	outputList:	Array of array for storing outputs of forward computation. Pass NULL if you want to ignore it.
 *	@param	errList:	Array of array for storing error (desire - output) before backpropagation. Pass NULL if you want to ignore it.
 *	@param	timeStep:	Time step of recurrent training.
 *	@param	gradLimit:	Gradient limit for recurrent training.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	0.1.0
 */

void rnn_forward_computation(ann_t ann, double* input, double* output);
/**
 *	@fn		void rnn_forward_computation(ann_t ann, double* input, double* output);
 *	@brief	Processing recurrent neural network forward computation.
 *	@param	ann:	Target ann_t type variable.
 *	@param	input:	Input array.
 *	@param	output:	Array for storing outputs.
 *	@since	0.1.0
 */

void rnn_forward_computation_erase(ann_t ann);
/**
 *	@fn		void rnn_forward_computation_erase(ann_t ann);
 *	@brief	Erase memory of recurrent neural network.
 *	@param	ann:	Target ann_t type variable.
 *	@since	0.1.0
 */

void rnn_bptt_erase(ann_t ann);
/**
 *	@fn		void rnn_bptt_erase(ann_t ann);
 *	@brief	Erase memory of backpropagation through time.
 *	@param	ann:	Target ann_t type variable.
 *	@since	0.1.0
 */

void rnn_bptt_adjust_network(ann_t ann, double learningRate, double momentumCoef, double gradLimit);
/**
 *	@fn		void rnn_bptt_adjust_network(ann_t ann, double learningRate, double momentumCoef, double gradLimit);
 *	@brief	Adjust recurrent neural netwrok by the gradients store in nodes.
 *	@param	ann:	Target ann_t type variable.
 *	@param	learningRate:	Custom learning rate.
 *	@param	momentumCoef:	Custom momentum coefficient.
 *	@param	gradLimit:	Gradient limit for recurrent training.
 *	@since	0.1.0
 */

int rnn_bptt_sum_gradient(ann_t ann, double* dError);
/**
 *	@fn		int rnn_bptt_sum_gradient(ann_t ann, double* dError);
 *	@brief	Summation gradients into neural nodes.
 *	@param	ann:	Target ann_t type variable.
 *	@param	dError:	Differential value of error value in cost function.
 *	@return	Return value could be describe by #ANN_RETUEN_VALUE.
 *	@since	1.0.0
 */

#ifdef __cplusplus
}
#endif

#endif
