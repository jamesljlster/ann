#include <assert.h>
#include <stdlib.h>

#include "ann.h"
#include "ann_builtin_math.h"
#include "ann_private.h"

const char* ann_get_transfer_func_name(int tFuncIndex)
{
    if (tFuncIndex < 0 || tFuncIndex >= ANN_TFUNC_RESERVED)
    {
        return NULL;
    }
    else
    {
        return ann_transfer_func_name[tFuncIndex];
    }
}

int ann_get_inputs(ann_t ann)
{
    ann_config_t annCfg;

    annCfg = ann_get_config(ann);

    return ann_config_get_inputs(annCfg);
}

int ann_get_outputs(ann_t ann)
{
    ann_config_t annCfg;

    annCfg = ann_get_config(ann);

    return ann_config_get_outputs(annCfg);
}

int ann_get_hidden_layers(ann_t ann)
{
    ann_config_t annCfg;

    annCfg = ann_get_config(ann);

    return ann_config_get_hidden_layers(annCfg);
}

int ann_get_hidden_nodes(ann_t ann, int hiddenLayerIndex)
{
    ann_config_t annCfg;

    annCfg = ann_get_config(ann);

    return ann_config_get_hidden_nodes(annCfg, hiddenLayerIndex);
}

int ann_get_transfer_func(ann_t ann)
{
    ann_config_t annCfg;

    annCfg = ann_get_config(ann);

    return ann_config_get_transfer_func(annCfg);
}

int ann_get_transfer_func_of_layer(ann_t ann, int layerIndex)
{
    ann_config_t annCfg;

    annCfg = ann_get_config(ann);

    return ann_config_get_transfer_func_of_layer(annCfg, layerIndex);
}

float ann_get_learning_rate(ann_t ann)
{
    ann_config_t annCfg;

    annCfg = ann_get_config(ann);

    return ann_config_get_learning_rate(annCfg);
}

float ann_get_momentum_coef(ann_t ann)
{
    ann_config_t annCfg;

    annCfg = ann_get_config(ann);

    return ann_config_get_momentum_coef(annCfg);
}

ann_config_t ann_get_config(ann_t ann)
{
    struct ANN_STRUCT* annRef = ann;

    return &annRef->config;
}

int ann_config_get_inputs(ann_config_t config)
{
    struct ANN_CONFIG_STRUCT* cfgRef = config;

    return cfgRef->inputs;
}

int ann_config_get_outputs(ann_config_t config)
{
    struct ANN_CONFIG_STRUCT* cfgRef = config;

    return cfgRef->outputs;
}

int ann_config_get_hidden_layers(ann_config_t config)
{
    struct ANN_CONFIG_STRUCT* cfgRef = config;

    if (cfgRef->layers > 0)
    {
        return cfgRef->layers - 2;
    }
    else
    {
        return 0;
    }
}

int ann_config_get_hidden_nodes(ann_config_t config, int hiddenLayerIndex)
{
    int layerIndex;
    struct ANN_CONFIG_STRUCT* cfgRef = config;

    assert(cfgRef->nodeList != NULL);

    layerIndex = hiddenLayerIndex + 1;

    assert(layerIndex > 0 && layerIndex < cfgRef->layers - 1);

    return cfgRef->nodeList[layerIndex];
}

int ann_config_get_transfer_func(ann_config_t config)
{
    struct ANN_CONFIG_STRUCT* cfgRef = config;

    return cfgRef->tFuncRoot;
}

int ann_config_get_transfer_func_of_layer(ann_config_t config, int layerIndex)
{
    struct ANN_CONFIG_STRUCT* cfgRef = config;

    if (cfgRef->tFuncRoot < ANN_TFUNC_AMOUNT)
    {
        return cfgRef->tFuncRoot;
    }
    else if (cfgRef->tFuncRoot == ANN_TFUNC_MULTIPLE)
    {
        assert(cfgRef->tFuncList != NULL);
        return cfgRef->tFuncList[layerIndex];
    }
    else if (cfgRef->tFuncRoot == ANN_TFUNC_CUSTOM)
    {
        return ANN_TFUNC_CUSTOM;
    }
    else
    {
        return ANN_INFO_NOT_FOUND;
    }
}

float ann_config_get_learning_rate(ann_config_t config)
{
    struct ANN_CONFIG_STRUCT* cfgRef = config;

    return cfgRef->learningRate;
}

float ann_config_get_momentum_coef(ann_config_t config)
{
    struct ANN_CONFIG_STRUCT* cfgRef = config;

    return cfgRef->momentumCoef;
}

float ann_get_weight(ann_t ann, int layerIndex, int preNodeIndex, int nodeIndex)
{
    struct ANN_STRUCT* annRef;
    struct ANN_LAYER* preLayer;
    struct ANN_LAYER* layerRef;
    struct ANN_CONFIG_STRUCT* cfgRef;

    annRef = ann;
    cfgRef = &annRef->config;

    // Checking
    assert(annRef->layerList != NULL);
    assert(layerIndex > 0 && layerIndex < cfgRef->layers);

    preLayer = &annRef->layerList[layerIndex - 1];
    layerRef = &annRef->layerList[layerIndex];

    assert(preNodeIndex >= 0 && preNodeIndex < preLayer->nodeCount);
    assert(nodeIndex >= 0 && nodeIndex < layerRef->nodeCount);

    return layerRef->nodeList[nodeIndex].weight[preNodeIndex];
}

float rnn_get_recurrent_weight(ann_t ann, int preNodeIndex, int nodeIndex)
{
    struct ANN_STRUCT* annRef;
    struct ANN_LAYER* preLayer;
    struct ANN_LAYER* layerRef;
    struct ANN_CONFIG_STRUCT* cfgRef;

    annRef = ann;
    cfgRef = &annRef->config;

    // Checking
    assert(annRef->layerList != NULL);
    assert(cfgRef->layers > 2);

    // Set layer reference
    preLayer = &annRef->layerList[cfgRef->layers - 2];
    layerRef = &annRef->layerList[1];

    assert(preNodeIndex >= 0 && preNodeIndex < preLayer->nodeCount);
    assert(nodeIndex >= 0 && nodeIndex < layerRef->nodeCount);
    assert(layerRef->nodeList[nodeIndex].rWeight != NULL);

    return layerRef->nodeList[nodeIndex].rWeight[preNodeIndex];
}

float ann_get_threshold(ann_t ann, int layerIndex, int nodeIndex)
{
    struct ANN_STRUCT* annRef;
    struct ANN_LAYER* layerRef;
    struct ANN_CONFIG_STRUCT* cfgRef;

    annRef = ann;
    cfgRef = &annRef->config;

    // Checking
    assert(annRef->layerList != NULL);
    assert(layerIndex >= 0 && layerIndex < cfgRef->layers);

    layerRef = &annRef->layerList[layerIndex];

    assert(nodeIndex >= 0 && nodeIndex < layerRef->nodeCount);

    return layerRef->nodeList[nodeIndex].threshold;
}
