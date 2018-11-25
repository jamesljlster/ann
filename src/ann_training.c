#include <stdlib.h>
#include <string.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int ann_training_gradient_custom(ann_t ann, float learningRate,
                                 float momentumCoef, float* input,
                                 float* desire, float* output, float* err)
{
    int i;
    int retValue = ANN_NO_ERROR;

    float* outputStore = NULL;
    float* errorStore = NULL;

    struct ANN_STRUCT* annRef;
    struct ANN_CONFIG_STRUCT* cfgRef;

    LOG("enter");

    // Get reference
    annRef = ann;
    cfgRef = &annRef->config;

    // Memory allocation
    outputStore = calloc(cfgRef->outputs, sizeof(float));
    errorStore = calloc(cfgRef->outputs, sizeof(float));
    if (outputStore == NULL || errorStore == NULL)
    {
        retValue = ANN_MEM_FAILED;
        goto RET;
    }

    // Forward computation
    ann_forward_computation(ann, input, outputStore);

    // Find error
    for (i = 0; i < cfgRef->outputs; i++)
    {
        errorStore[i] = desire[i] - outputStore[i];
    }

    // Backpropagation
    ann_backpropagation(ann, learningRate, momentumCoef, errorStore);

    if (output != NULL)
        memcpy(output, outputStore, cfgRef->outputs * sizeof(float));

    if (err != NULL) memcpy(err, errorStore, cfgRef->outputs * sizeof(float));

RET:
    if (outputStore != NULL) free(outputStore);

    if (errorStore != NULL) free(errorStore);

    LOG("exit");
    return retValue;
}

int ann_training_gradient(ann_t ann, float* input, float* desire, float* output,
                          float* err)
{
    int i;
    int retValue = ANN_NO_ERROR;

    float* outputStore = NULL;
    float* errorStore = NULL;

    struct ANN_STRUCT* annRef;
    struct ANN_CONFIG_STRUCT* cfgRef;

    LOG("enter");

    // Get reference
    annRef = ann;
    cfgRef = &annRef->config;

    // Memory allocation
    outputStore = calloc(cfgRef->outputs, sizeof(float));
    errorStore = calloc(cfgRef->outputs, sizeof(float));
    if (outputStore == NULL || errorStore == NULL)
    {
        retValue = ANN_MEM_FAILED;
        goto RET;
    }

    // Forward computation
    ann_forward_computation(ann, input, outputStore);

    // Find error
    for (i = 0; i < cfgRef->outputs; i++)
    {
        errorStore[i] = desire[i] - outputStore[i];
    }

    // Backpropagation
    ann_backpropagation(ann, cfgRef->learningRate, cfgRef->momentumCoef,
                        errorStore);

    if (output != NULL)
        memcpy(output, outputStore, cfgRef->outputs * sizeof(float));

    if (err != NULL) memcpy(err, errorStore, cfgRef->outputs * sizeof(float));

RET:
    if (outputStore != NULL) free(outputStore);

    if (errorStore != NULL) free(errorStore);

    LOG("exit");
    return retValue;
}
