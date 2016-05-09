#include <stdlib.h>
#include <math.h>

#include "NNLIB.h"

int NNLIB_CalcError(struct NN_STRUCT* nStructPtr, double* errList, double* desireOutput)
{
    int i;
    
    double* outputStore;
    
    // Memory Allocation: Space for storing output values
    outputStore = (double*)calloc(nStructPtr->outputNodeCount, sizeof(double));
    if(outputStore == NULL)
    {
        return -1;
    }
    
    // Get Neural Network output
    NNLIB_GetOutput(nStructPtr, outputStore);
    
    // Calculate Error
    for(i = 0; i < nStructPtr->outputNodeCount; i++)
    {
        errList[i] = desireOutput[i] - outputStore[i];
    }
    
    // Cleanup
    free(outputStore);
    
    return 0;
}

int NNLIB_ForwardComputation(struct NN_STRUCT* nStructPtr, double* input, double* outputStore)
{
    int i, j, k;
    
    double calcTmp;
    
    struct NN_LAYER* nLayerRef = nStructPtr->nLayerHandle;
    
    // Copy Input to Layer 0
    for(i=0; i<nStructPtr->inputNodeCount; i++)
    {
        nLayerRef[0].nodeList[i].output = input[i];
    }
    
    // Forward Computation
    for(i=1; i<nStructPtr->layerCount; i++)
    {
        for(j=0; j<nLayerRef[i].nodeCount; j++)
        {
            calcTmp = 0;
            for(k=0; k<nLayerRef[i - 1].nodeCount; k++)
            {
                calcTmp += nLayerRef[i - 1].nodeList[k].output * nLayerRef[i].nodeList[j].weight[k];
            }
            nLayerRef[i].nodeList[j].sCalc = calcTmp;
            
            if(nLayerRef[i].activeFunc == NULL)
            {
                nLayerRef[i].nodeList[j].output = nLayerRef[i].nodeList[j].sCalc - nLayerRef[i].nodeList[j].threshold;
            }
            else
            {
                nLayerRef[i].nodeList[j].output = nLayerRef[i].activeFunc(nLayerRef[i].nodeList[j].sCalc - nLayerRef[i].nodeList[j].threshold);
            }
        }
    }
    
    // Get Output
    if(outputStore != NULL)
    {
        for(i = 0; i < nStructPtr->outputNodeCount; i++)
        {
            outputStore[i] = nLayerRef[nStructPtr->layerCount - 1].nodeList[i].output;
        }
    }

    return 0;
}
