#include <stdlib.h>
#include <string.h>

#include "ann.h"
#include "ann_private.h"

#include "debug.h"

int ann_config_clone(ann_config_t* dstCfgPtr, ann_config_t srcCfg)
{
    int iResult;
    int retValue = ANN_NO_ERROR;
    ann_config_t tmpCfg = NULL;

    // Allocate memory
    tmpCfg = malloc(sizeof(struct ANN_CONFIG_STRUCT));
    if (tmpCfg == NULL)
    {
        retValue = ANN_MEM_FAILED;
        goto RET;
    }

    // Clone config
    iResult = ann_clone_config_struct(tmpCfg, srcCfg);
    if (iResult != ANN_NO_ERROR)
    {
        retValue = iResult;
        goto RET;
    }

    // Assig value
    *dstCfgPtr = tmpCfg;

RET:
    return retValue;
}

int ann_clone_config_struct(struct ANN_CONFIG_STRUCT* dst,
                            struct ANN_CONFIG_STRUCT* src)
{
    int i;

    LOG("enter");

    // Zero memory
    ann_config_zeromem(dst);

    // Copy setting
    dst->inputs = src->inputs;
    dst->outputs = src->outputs;
    dst->layers = src->layers;

    dst->learningRate = src->learningRate;
    dst->momentumCoef = src->momentumCoef;

    // Clone transfer function list
    dst->tFuncRoot = src->tFuncRoot;
    if (src->tFuncList != NULL)
    {
        dst->tFuncList = calloc(dst->layers, sizeof(int));
        if (dst->tFuncList == NULL)
        {
            return ANN_MEM_FAILED;
        }
        else
        {
            for (i = 0; i < dst->layers; i++)
            {
                dst->tFuncList[i] = src->tFuncList[i];
            }
        }
    }

    // Clone nodes list
    dst->nodeList = calloc(dst->layers, sizeof(int));
    if (dst->nodeList == NULL)
    {
        return ANN_MEM_FAILED;
    }
    else
    {
        for (i = 0; i < dst->layers; i++)
        {
            dst->nodeList[i] = src->nodeList[i];
        }
    }

    LOG("exit");

    return ANN_NO_ERROR;
}

int ann_clone(ann_t* dstAnnPtr, ann_t srcAnn)
{
    int i, j;
    int iResult;
    int retValue = ANN_NO_ERROR;

    struct ANN_STRUCT* annRef;
    struct ANN_CONFIG_STRUCT* cfgRef;
    struct ANN_LAYER* dstLayerRef;
    struct ANN_LAYER* srcLayerRef;

    ann_t ann = NULL;
    ann_config_t srcCfg = NULL;

    // Get source config
    srcCfg = ann_get_config(srcAnn);

    // Create neural network
    iResult = ann_create(&ann, srcCfg);
    if (iResult != ANN_NO_ERROR)
    {
        retValue = iResult;
        goto RET;
    }

    // Set reference
    annRef = ann;
    cfgRef = &annRef->config;
    dstLayerRef = annRef->layerList;
    srcLayerRef = ((struct ANN_STRUCT*)srcAnn)->layerList;

    // Copy weight and threshold
    for (i = 1; i < cfgRef->layers; i++)
    {
        for (j = 0; j < dstLayerRef[i].nodeCount; j++)
        {
            dstLayerRef[i].nodeList[j].threshold =
                srcLayerRef[i].nodeList[j].threshold;
            memcpy(dstLayerRef[i].nodeList[j].weight,
                   srcLayerRef[i].nodeList[j].weight,
                   sizeof(float) * dstLayerRef[i - 1].nodeCount);
        }
    }

    // Copy recurrent weight
    if (cfgRef->layers > 2)
    {
        for (j = 0; j < dstLayerRef[1].nodeCount; j++)
        {
            memcpy(dstLayerRef[1].nodeList[j].rWeight,
                   srcLayerRef[1].nodeList[j].rWeight,
                   sizeof(float) * dstLayerRef[cfgRef->layers - 2].nodeCount);
        }
    }

    // Assign value
    *dstAnnPtr = ann;

RET:
    return retValue;
}
