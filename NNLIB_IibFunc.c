#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "NNLIB.h"

int NNLIB_Config(struct NN_STRUCT* nStructPtr, double learningRate, int inputNodeCount, int outputNodeCount, int hiddenLayerCount, ...)
{
    int i;
    
    va_list argList;
    
    // Set Values
    nStructPtr->learningRate = learningRate;
    nStructPtr->inputNodeCount = inputNodeCount;
    nStructPtr->outputNodeCount = outputNodeCount;
    nStructPtr->layerCount = hiddenLayerCount + 2;
    
    // Memory Allocation: Node count of each hidden layer
    nStructPtr->nodesEachLayer = (int*)calloc(hiddenLayerCount, sizeof(int));
    if(nStructPtr->nodesEachLayer == NULL)
    {
        return -1;
    }
    
    // Save node count of each hidden layer
    va_start(argList, hiddenLayerCount);
    for(i=0; i<hiddenLayerCount; i++)
    {
        nStructPtr->nodesEachLayer[i] = va_arg(argList, int);
    }
    va_end(argList);
    
    return 0;
}

int NNLIB_GetOutput(struct NN_STRUCT* nStructPtr, double* outputStore)
{
    int i;
    
    struct NN_LAYER* nLayerRef = nStructPtr->nLayerHandle;
    
    for(i=0; i<nStructPtr->outputNodeCount; i++)
    {
        outputStore[i] = nLayerRef[nStructPtr->layerCount - 1].nodeList[i].output;
    }
    
    return 0;
}

int NNLIB_SetdActiveFunc(struct NN_STRUCT* nStructPtr, int assignAction, double (*dActiveFunc)(double), ...)
{
    int i;
    
    va_list argList;
    
    if(assignAction == NNLIB_MANUALLY_ASSIGN)
    {
        nStructPtr->nLayerHandle[1].dActiveFunc = dActiveFunc;
        
        va_start(argList, dActiveFunc);
        for(i=2; i<nStructPtr->layerCount; i++)
        {
            nStructPtr->nLayerHandle[i].dActiveFunc = va_arg(argList, double (*)(double));
        }
        va_end(argList);
    }
    else
    {
        for(i=1; i<nStructPtr->layerCount; i++)
        {
            nStructPtr->nLayerHandle[i].dActiveFunc = dActiveFunc;
        }
    }
    
    return 0;
}

int NNLIB_SetActiveFunc(struct NN_STRUCT* nStructPtr, int assignAction, double (*activeFunc)(double), ...)
{
    int i;
    
    va_list argList;
    
    if(assignAction == NNLIB_MANUALLY_ASSIGN)
    {
        nStructPtr->nLayerHandle[1].activeFunc = activeFunc;
        
        va_start(argList, activeFunc);
        for(i=2; i<nStructPtr->layerCount; i++)
        {
            nStructPtr->nLayerHandle[i].activeFunc = va_arg(argList, double (*)(double));
        }
        va_end(argList);
    }
    else
    {
        for(i=1; i<nStructPtr->layerCount; i++)
        {
            nStructPtr->nLayerHandle[i].activeFunc = activeFunc;
        }
    }
    
    return 0;
}

int NNLIB_RandWeight(struct NN_STRUCT* nStructPtr)
{
    int i, j, k;
    
    struct NN_LAYER* nLayerRef = nStructPtr->nLayerHandle;
    
    for(i=1; i<nStructPtr->layerCount; i++)
    {
        for(j=0; j<nLayerRef[i].nodeCount; j++)
        {
            for(k=0; k<nLayerRef[i - 1].nodeCount; k++)
            {
                nLayerRef[i].nodeList[j].weight[k] = ((double)(rand()%2001 - 1000) / 1000);
            }
        }
    }
    
    return 0;
}

int NNLIB_Delete(struct NN_STRUCT* nStructPtr)
{
    int i, j;
    
    struct NN_LAYER* nLayerRef = nStructPtr->nLayerHandle;
    
    free(nLayerRef[0].nodeList);
    for(i=1; i<nStructPtr->layerCount; i++)
    {
        for(j=0; j<nLayerRef[i].nodeCount; j++)
        {
            //free(nLayerRef[i].nodeList[j].input);
            free(nLayerRef[i].nodeList[j].weight);
        }
        
        free(nLayerRef[i].nodeList);
    }
    
    free(nStructPtr->nLayerHandle);
    free(nStructPtr->nodesEachLayer);
    
    return 0;
}

int NNLIB_Create(struct NN_STRUCT* nStructPtr)
{
    int i, j;
    struct NN_LAYER* nLayerRef = NULL;

    // Create NN_LAYER
    nStructPtr->nLayerHandle = (struct NN_LAYER*)calloc(nStructPtr->layerCount, sizeof(struct NN_LAYER));
    if(nStructPtr->nLayerHandle == NULL)
    {
        return -1;
    }
    
    // Set Reference of nLayerHandle
    nLayerRef = nStructPtr->nLayerHandle;

    // Create nodes
    for(i=0; i<nStructPtr->layerCount; i++)
    {
        if(i == 0)
        {
            // Memory Allocation: Layer Nodes
            nLayerRef[i].nodeList = (struct NN_NODE*)calloc(nStructPtr->inputNodeCount, sizeof(struct NN_NODE));
            if(nLayerRef[i].nodeList == NULL)
            {
                return -1;
            }

            // Setup node count under layer
            nLayerRef[i].nodeCount = nStructPtr->inputNodeCount;
        }
        else if(i == nStructPtr->layerCount - 1)
        {
            // Memory Allocation: Layer Nodes
            nLayerRef[i].nodeList = (struct NN_NODE*)calloc(nStructPtr->outputNodeCount, sizeof(struct NN_NODE));
            if(nLayerRef[i].nodeList == NULL)
            {
                return -1;
            }

            // Setup node count under layer
            nLayerRef[i].nodeCount = nStructPtr->outputNodeCount;
        }
        else
        {
            // Memory Allocation: Layer Nodes
            nLayerRef[i].nodeList = (struct NN_NODE*)calloc(nStructPtr->nodesEachLayer[i - 1], sizeof(struct NN_NODE));
            if(nLayerRef[i].nodeList == NULL)
            {
                return -1;
            }

            // Setup node count under layer
            nLayerRef[i].nodeCount = nStructPtr->nodesEachLayer[i - 1];
        }

        // Setup nodes
        for(j=0; j<nLayerRef[i].nodeCount; j++)
        {
            if(i == 0)
            {
                nLayerRef[i].nodeList[j].nodeType = INPUT_NODE;

                //nLayerRef[i].nodeList[j].input = NULL;
                nLayerRef[i].nodeList[j].weight = NULL;
            }
            else
            {
                if(i == nStructPtr->layerCount - 1)
                {
                    nLayerRef[i].nodeList[j].nodeType = OUTPUT_NODE;
                }
                else
                {
                    nLayerRef[i].nodeList[j].nodeType = HIDDEN_NODE;
                }

                /*nLayerRef[i].nodeList[j].input = (double*)calloc(nLayerRef[i-1].nodeCount, sizeof(double));
                if(nLayerRef[i].nodeList[j].input == NULL)
                {
                    return -1;
                }*/

                nLayerRef[i].nodeList[j].weight = (double*)calloc(nLayerRef[i-1].nodeCount, sizeof(double));
                if(nLayerRef[i].nodeList[j].weight == NULL)
                {
                    return -1;
                }
            }
            
            nLayerRef[i].nodeList[j].threshold = 0.0;
        }
    }

    // Apply nLayerRef to nLayerHandle
    nStructPtr->nLayerHandle = nLayerRef;

    return 0;
}
