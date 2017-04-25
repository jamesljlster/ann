#ifndef __ANN_TYPES_H__
#define __ANN_TYPES_H__

struct ANN_NODE
{
	double* rWeight;
	double* weight;
	double* deltaW;

	int queueLen;
	double* queue;

	double threshold;
	double deltaTh;

	double delta;

	double rHold;
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

#endif
