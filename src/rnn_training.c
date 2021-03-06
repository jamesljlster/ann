#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int rnn_training_gradient(ann_t ann, float** inputList, float** desireList,
                          float** outputList, float** errList, int timeStep,
                          float gradLimit)
{
    struct ANN_STRUCT* annRef = NULL;
    struct ANN_CONFIG_STRUCT* cfgRef = NULL;

    // Get referenct
    annRef = ann;
    cfgRef = &annRef->config;

    return rnn_training_gradient_custom(
        ann, cfgRef->learningRate, cfgRef->momentumCoef, inputList, desireList,
        outputList, errList, timeStep, gradLimit);
}

int rnn_training_gradient_custom(ann_t ann, float learningRate,
                                 float momentumCoef, float** inputList,
                                 float** desireList, float** outputList,
                                 float** errList, int timeStep, float gradLimit)
{
    int i, j;
    int iResult;
    int retValue = ANN_NO_ERROR;

    float* outputStore = NULL;
    float* errorStore = NULL;

    struct ANN_STRUCT* annRef = NULL;
    struct ANN_CONFIG_STRUCT* cfgRef = NULL;

    LOG("enter");

    // Get referenct
    annRef = ann;
    cfgRef = &annRef->config;

    // Memory allocation
    outputStore = calloc(cfgRef->outputs * timeStep, sizeof(float));
    errorStore = calloc(cfgRef->outputs * timeStep, sizeof(float));
    if (outputStore == NULL || errorStore == NULL)
    {
        retValue = ANN_MEM_FAILED;
        goto RET;
    }

    // Set max time step
    iResult = rnn_bptt_set_max_timestep(ann, timeStep);
    if (iResult != ANN_NO_ERROR)
    {
        retValue = iResult;
        goto RET;
    }

    // Recurrent training
    for (i = 0; i < timeStep; i++)
    {
        // Forward computation
        rnn_forward_computation(ann, inputList[i],
                                &outputStore[i * cfgRef->outputs]);

        // Find error
        if (desireList[i] != NULL)
        {
            for (j = 0; j < cfgRef->outputs; j++)
            {
                errorStore[i * cfgRef->outputs + j] =
                    desireList[i][j] - outputStore[i * cfgRef->outputs + j];
            }
        }
        else
        {
            for (j = 0; j < cfgRef->outputs; j++)
            {
                errorStore[i * cfgRef->outputs + j] = 0;
            }
        }

        // Backpropagation
        rnn_bptt_sum_gradient(ann, &errorStore[i * cfgRef->outputs]);
    }

    // Adjust network
    rnn_bptt_adjust_network(ann, learningRate, momentumCoef, gradLimit);

    // Erase
    rnn_bptt_erase(ann);
    rnn_forward_computation_erase(ann);

    // Copy values
    if (outputList != NULL)
    {
        for (i = 0; i < timeStep; i++)
        {
            for (j = 0; j < cfgRef->outputs; j++)
            {
                outputList[i][j] = outputStore[i * cfgRef->outputs + j];
            }
        }
    }

    if (errList != NULL)
    {
        for (i = 0; i < timeStep; i++)
        {
            for (j = 0; j < cfgRef->outputs; j++)
            {
                errList[i][j] = errorStore[i * cfgRef->outputs + j];
            }
        }
    }

RET:
    if (outputStore != NULL) free(outputStore);

    if (errorStore != NULL) free(errorStore);

    return retValue;
}
