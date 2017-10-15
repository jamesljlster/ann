#ifndef __ANN_TYPES_H__
#define __ANN_TYPES_H__

struct ANN_NODE
{
	double* rWeight;		// Recurrent weight list
	double* rWeightDelta;	// Adjust delta summation of recurrent weight
	double* deltaRW;		// Momentum of recurrent weight

	double* weight;			// Weight list
	double* weightDelta;	// Adjust delta summation of weight
	double* deltaW;			// Momentum of weight

	double* outputQueue;	// Output queue
	double* sCalcQueue;		// sCalc queue

	double threshold;		// Threshold of the node
	double thresholdDelta;	// Adjust delta summation of threshold
	double deltaTh;			// Momentum of threshold

	double delta;		// For bp calculation
	double deltaHold;	// Gradient hold for bp calculation

	double rHold;		// For recurrent forward computation.
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

	int tFuncRoot;	// Transfer function root setting
	int* tFuncList;	// Transfer function setting of each layers

	double learningRate;
	double momentumCoef;

	int* nodeList;
};

struct ANN_STRUCT
{
	int queueHead;
	int queueTail;
	int queueSize;			// Memory length of recurrent queue
    struct ANN_LAYER* layerList;

	struct ANN_CONFIG_STRUCT config;
};

#endif
