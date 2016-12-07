#include <stdlib.h>

#include "NNLIB.h"
#include "Alloc2DArray.h"

#define ADJUST_THRESHOLD

#ifdef DEBUG
#include <stdio.h>
#endif

int NNLIB_BackPropagation_Gradient(struct NN_STRUCT* nStructPtr, double learningRate, double* dError)
{
    int i, j, k;
    
    double** deltaList = NULL;
    
    struct NN_LAYER* nLayerRef = nStructPtr->nLayerHandle;
    
    // Memory Allocation: Delta List
    deltaList = (double**)calloc(nStructPtr->layerCount, sizeof(double*));
    if(deltaList == NULL)
    {
        return -1;
    }
    
    for(i = 0; i < nStructPtr->layerCount; i++)
    {
        deltaList[i] = calloc(nLayerRef[i].nodeCount, sizeof(double));
        if(deltaList[i] == NULL)
        {
            // Free Allocated Memory
            for(j = 0; j < i; j++)
            {
                free(deltaList[j]);
            }
            free(deltaList);
            
            return -1;
        }
    }

    for(i = nStructPtr->layerCount - 1; i > 0; i--)
    {
        // Process Delta List
        if(i == nStructPtr->layerCount - 1)
        {
            for(j = 0; j < nLayerRef[i].nodeCount; j++)
            {
                #ifdef ADJUST_THRESHOLD
                deltaList[i][j] = dError[j] * nLayerRef[i].dActiveFunc(nLayerRef[i].nodeList[j].sCalc - nLayerRef[i].nodeList[j].threshold);
                #else
                deltaList[i][j] = dError[j] * nLayerRef[i].dActiveFunc(nLayerRef[i].nodeList[j].sCalc);
                #endif
            }
        }
        else
        {
            for(j = 0; j < nLayerRef[i].nodeCount; j++)
            {
                deltaList[i][j] = 0;
                for(k = 0; k < nLayerRef[i + 1].nodeCount; k++)
                {
                    deltaList[i][j] += deltaList[i + 1][k] * nLayerRef[i + 1].nodeList[k].weight[j];
                }
                deltaList[i][j] *= nLayerRef[i].dActiveFunc(nLayerRef[i].nodeList[j].sCalc);
            }
        }
    }
    
    for(i = nStructPtr->layerCount - 1; i > 0; i--)
    {
        // Adjust Weights
        for(j = 0; j < nLayerRef[i].nodeCount; j++)
        {
            #ifdef ADJUST_THRESHOLD
            nLayerRef[i].nodeList[j].threshold -= learningRate * deltaList[i][j];
            #endif
            
            for(k = 0; k < nLayerRef[i - 1].nodeCount; k++)
            {
                nLayerRef[i].nodeList[j].weight[k] += learningRate * deltaList[i][j] * nLayerRef[i - 1].nodeList[k].output;
            }
        }
    }
    
    // Cleanup
    for(i = 0; i < nStructPtr->layerCount; i++)
    {
        free(deltaList[i]);
    }
    free(deltaList);
    
    return 0;
}

int NNLIB_SLearning_Gradient(struct NN_STRUCT* nStructPtr, double* input, double* desireOutput, double* fwCompOut, double* fwCompErr)
{
    int i, j, k;
    
    double** deltaList = NULL;
    
    struct NN_LAYER* nLayerRef = nStructPtr->nLayerHandle;
    
    // Memory Allocation: Delta List
    deltaList = (double**)calloc(nStructPtr->layerCount, sizeof(double*));
    if(deltaList == NULL)
    {
        return -1;
    }
    
    for(i = 0; i < nStructPtr->layerCount; i++)
    {
        deltaList[i] = calloc(nLayerRef[i].nodeCount, sizeof(double));
        if(deltaList[i] == NULL)
        {
            // Free Allocated Memory
            for(j = 0; j < i; j++)
            {
                free(deltaList[j]);
            }
            free(deltaList);
            
            return -1;
        }
    }
    
    // Run Forward Compution
    NNLIB_ForwardComputation(nStructPtr, input, NULL);
    
    for(i = nStructPtr->layerCount - 1; i > 0; i--)
    {
        // Process Delta List
        if(i == nStructPtr->layerCount - 1)
        {
            for(j = 0; j < nLayerRef[i].nodeCount; j++)
            {
                #ifdef ADJUST_THRESHOLD
                deltaList[i][j] = (desireOutput[j] - nLayerRef[i].nodeList[j].output) * nLayerRef[i].dActiveFunc(nLayerRef[i].nodeList[j].sCalc - nLayerRef[i].nodeList[j].threshold);
                #else
                deltaList[i][j] = (desireOutput[j] - nLayerRef[i].nodeList[j].output) * nLayerRef[i].dActiveFunc(nLayerRef[i].nodeList[j].sCalc);
                #endif
            }
        }
        else
        {
            for(j = 0; j < nLayerRef[i].nodeCount; j++)
            {
                deltaList[i][j] = 0;
                for(k = 0; k < nLayerRef[i + 1].nodeCount; k++)
                {
                    deltaList[i][j] += deltaList[i + 1][k] * nLayerRef[i + 1].nodeList[k].weight[j];
                }
                deltaList[i][j] *= nLayerRef[i].dActiveFunc(nLayerRef[i].nodeList[j].sCalc);
            }
        }
    }
    
    for(i = nStructPtr->layerCount - 1; i > 0; i--)
    {
        // Adjust Weights
        for(j = 0; j < nLayerRef[i].nodeCount; j++)
        {
            #ifdef ADJUST_THRESHOLD
            nLayerRef[i].nodeList[j].threshold -= nStructPtr->learningRate * deltaList[i][j];
            #endif
            
            for(k = 0; k < nLayerRef[i - 1].nodeCount; k++)
            {
                nLayerRef[i].nodeList[j].weight[k] += nStructPtr->learningRate * deltaList[i][j] * nLayerRef[i - 1].nodeList[k].output;
            }
        }
    }
    
    // Output Forward Computation Result
    if(fwCompOut != NULL)
    {
        for(i = 0; i < nStructPtr->outputNodeCount; i++)
        {
            fwCompOut[i] = nLayerRef[nStructPtr->layerCount - 1].nodeList[i].output;
        }
    }
    
    // Output Error
    if(fwCompErr != NULL)
    {
        for(i = 0; i < nStructPtr->outputNodeCount; i++)
        {
            fwCompErr[i] = desireOutput[i] - nLayerRef[nStructPtr->layerCount - 1].nodeList[i].output;
        }
    }
    
    // Cleanup
    for(i = 0; i < nStructPtr->layerCount; i++)
    {
        free(deltaList[i]);
    }
    free(deltaList);
    
    return 0;
}
