#include <stdio.h>
#include <stdlib.h>

#include "NNLIB.h"
#include "CMDL.h"
#include "ActiveFunc.h"

int CMD_CreateNN(CMD_FUNC_ARGLIST)
{
    int i, iResult;
    int tmpConvert;
    int bufProcIndex = 0;;
    
    // Checking
    if(*nnStatePtr == 1)
    {
        NNLIB_Delete(nStructPtr);
        *nnStatePtr = 0;
    }
    
    // Determine Neural Networks Detail
    if(*traStatePtr == 1)
    {
        nStructPtr->inputNodeCount = KEEL_GetInputs(*traDataPtr);
        nStructPtr->outputNodeCount = KEEL_GetOutputs(*traDataPtr);
    }
    else
    {
        // Get Input Nodes
        tmpConvert = 0;
        bufProcIndex = CMD_FindDash(comBuf, bufProcIndex, CMD_BUFFER_LEN);
        if(bufProcIndex > 0)
        {
            bufProcIndex++;
            if(comBuf[bufProcIndex] != '\0')
            {
                tmpConvert = atoi(&comBuf[bufProcIndex]);
            }
        }
        
        if(tmpConvert > 0)
        {
            nStructPtr->inputNodeCount = tmpConvert;
        }
        else
        {
            printf("Assign Input Nodes: ");
            scanf(" %d", &nStructPtr->inputNodeCount);
        }
        
        // Get Output Nodes
        tmpConvert = 0;
        bufProcIndex = CMD_FindDash(comBuf, bufProcIndex, CMD_BUFFER_LEN);
        if(bufProcIndex > 0)
        {
            bufProcIndex++;
            if(comBuf[bufProcIndex] != '\0')
            {
                tmpConvert = atoi(&comBuf[bufProcIndex]);
            }
        }
        
        if(tmpConvert > 0)
        {
            nStructPtr->outputNodeCount = tmpConvert;
        }
        else
        {
            printf("Assign Output Nodes: ");
            scanf(" %d", &nStructPtr->outputNodeCount);
        }
    }
    
    // Get Hidden Layer Count
    tmpConvert = 0;
    bufProcIndex = CMD_FindDash(comBuf, bufProcIndex, CMD_BUFFER_LEN);
    if(bufProcIndex > 0)
    {
        bufProcIndex++;
        if(comBuf[bufProcIndex] != '\0')
        {
            tmpConvert = atoi(&comBuf[bufProcIndex]);
        }
    }
    
    if(tmpConvert > 0)
    {
        nStructPtr->layerCount = tmpConvert;
    }
    else
    {
        printf("Assign Hidden Layer Amount: ");
        scanf(" %d", &nStructPtr->layerCount);
    }
    
    // Memory Allocation: Node count of each hidden layer
    if(nStructPtr->layerCount > 0)
    {
        nStructPtr->nodesEachLayer = (int*)calloc(nStructPtr->layerCount, sizeof(int));
        if(nStructPtr->nodesEachLayer == NULL)
        {
            printf("Memory Allocation Failed!\n");
            return -1;
        }
    }
    
    // Memory Allocation: Activation Function List
    nStructPtr->aFuncIndexList = (int*)calloc(nStructPtr->layerCount + 1, sizeof(int));
    if(nStructPtr->aFuncIndexList == NULL)
    {
        if(nStructPtr->nodesEachLayer != NULL) free(nStructPtr->nodesEachLayer);
        
        return -1;
    }
    
    for(i = 0; i < nStructPtr->layerCount; i++)
    {
        // Get Hidden Layer Count
        tmpConvert = 0;
        bufProcIndex = CMD_FindDash(comBuf, bufProcIndex, CMD_BUFFER_LEN);
        if(bufProcIndex > 0)
        {
            bufProcIndex++;
            if(comBuf[bufProcIndex] != '\0')
            {
                tmpConvert = atoi(&comBuf[bufProcIndex]);
            }
        }
        
        if(tmpConvert > 0)
        {
            nStructPtr->nodesEachLayer[i] = tmpConvert;
        }
        else
        {
            printf("Assign Hidden Layer %d Nodes: ", i);
            scanf(" %d", &nStructPtr->nodesEachLayer[i]);
        }
    }
    
    nStructPtr->layerCount += 2;
    
    #ifdef DEBUG
    printf("Input Node Count: %d\n", nStructPtr->inputNodeCount);
    printf("Output Node Count: %d\n", nStructPtr->outputNodeCount);
    printf("Layer Count: %d\n", nStructPtr->layerCount);
    
    for(i = 0; i < nStructPtr->layerCount - 2; i++)
    {
        printf("Hidden Layer %d Nodes: %d\n", i, nStructPtr->nodesEachLayer[i]);
    }
    #endif
    
    // Create Neural Networks
    iResult = NNLIB_Create(nStructPtr);
    if(iResult != 0)
    {
        printf("Failed to create neural networks!\n");
        return -1;
    }
    
    // Assign Activation Function
    NNLIB_SetActiveFunc(nStructPtr, NNLIB_ASSIGN_SAME_ACTFUNC, AFUNC_Sigmoidal);
    NNLIB_SetdActiveFunc(nStructPtr, NNLIB_ASSIGN_SAME_ACTFUNC, AFUNC_Sigmoidal_Derivative);
    
    // Rand Weights
    NNLIB_RandWeight(nStructPtr);
    
    *nnStatePtr = 1;
    
    return 0;
}
