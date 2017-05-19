#ifndef __ANN_TYPES_H__
#define __ANN_TYPES_H__

struct ANN_NODE
{
	double* rWeight;	// Recurrent weight list
	double* weight;		// Weight list
	double* deltaW;		// Momentum of weight

	double* outputQueue;	// Output queue
	double* sCalcQueue;		// sCalc queue

	double threshold;	// Threshold of the node
	double deltaTh;		// Momentum of threshold

	double delta;		// For bp calculation
	double deltaSum;	// Sum of bp delta for adjusting weight and threshold

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
	int transferFuncIndex;
	
	double learningRate;
	double momentumCoef;

	int* nodeList;
};

struct ANN_STRUCT
{
	int queueLen;			// Recurrent queue length
    struct ANN_LAYER* layerList;

	struct ANN_CONFIG_STRUCT config;
};

#endif
