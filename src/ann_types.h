#ifndef __ANN_TYPES_H__
#define __ANN_TYPES_H__

struct ANN_NODE
{
    float* rWeight;       // Recurrent weight list
    float* rWeightDelta;  // Adjust delta summation of recurrent weight
    float* deltaRW;       // Momentum of recurrent weight

    float* weight;       // Weight list
    float* weightDelta;  // Adjust delta summation of weight
    float* deltaW;       // Momentum of weight

    float* outputQueue;  // Output queue
    float* sCalcQueue;   // sCalc queue

    float threshold;       // Threshold of the node
    float thresholdDelta;  // Adjust delta summation of threshold
    float deltaTh;         // Momentum of threshold

    float delta;      // For bp calculation
    float deltaHold;  // Gradient hold for bp calculation

    float rHold;  // For recurrent forward computation.
    float sCalc;
    float output;
};

struct ANN_LAYER
{
    float (*activeFunc)(float);
    float (*dActiveFunc)(float);

    struct ANN_NODE* nodeList;
    int nodeCount;
};

struct ANN_CONFIG_STRUCT
{
    int inputs;
    int outputs;
    int layers;

    int tFuncRoot;   // Transfer function root setting
    int* tFuncList;  // Transfer function setting of each layers

    float learningRate;
    float momentumCoef;

    int* nodeList;
};

struct ANN_STRUCT
{
    int queueHead;
    int queueTail;
    int queueSize;  // Memory length of recurrent queue
    struct ANN_LAYER* layerList;

    struct ANN_CONFIG_STRUCT config;
};

#endif
