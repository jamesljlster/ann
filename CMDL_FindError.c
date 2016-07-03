#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "NNLIB.h"
#include "CMDL.h"
#include "Alloc2DArray.h"

int CMD_FindError(CMD_FUNC_ARGLIST)
{
    int i, j;
    int saveState;
    
    double avgError;
    double calcTmp;
    
    double** nnOutput;
    double** nnTarget;
    
    char pathBuf[CMD_BUFFER_LEN] = {0};
    
    FILE* tmpFile = NULL;
    
    // Checking
    if(*nnStatePtr != 1)
    {
        printf("No neural networks created!\n");
        return -1;
    }
    
    if(*traStatePtr != 1)
    {
        printf("No training dataset read!\n");
        return -1;
    }
    else if(KEEL_GetInputs(*traDataPtr) != nStructPtr->inputNodeCount || KEEL_GetOutputs(*traDataPtr) != nStructPtr->outputNodeCount)
    {
        printf("Training dataset is not suitable for current neural networks!\n");
        return -1;
    }
    
    // Get File Path
    saveState = CMD_GetFilePath(pathBuf, comBuf, NULL);
    
    // Memory Allocation
    nnOutput = (double**)Alloc2DArray(KEEL_GetDataAmount(*traDataPtr), nStructPtr->outputNodeCount, sizeof(double));
    if(nnOutput == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return -1;
    }
    
    nnTarget = (double**)Alloc2DArray(KEEL_GetDataAmount(*traDataPtr), nStructPtr->outputNodeCount, sizeof(double));
    if(nnTarget == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnOutput);
        return -1;
    }
    
    // Iteration
    for(i = 0; i < KEEL_GetDataAmount(*traDataPtr); i++)
    {
        // Forward Computation
        NNLIB_ForwardComputation(nStructPtr, KEEL_GetInputList(*traDataPtr, i), nnOutput[i]);
        
        // Copy Target and Output
        for(j = 0; j < nStructPtr->outputNodeCount; j++)
        {
            nnTarget[i][j] = KEEL_GetOutputList(*traDataPtr, i)[j];
        }
    }
    
    // Find Average Error
    avgError = 0;
    for(i = 0; i < KEEL_GetDataAmount(*traDataPtr); i++)
    {
        calcTmp = 0;
        for(j = 0; j < nStructPtr->outputNodeCount; j++)
        {
            calcTmp += fabs(nnTarget[i][j] - nnOutput[i][j]) / nnTarget[i][j];
        }
        calcTmp /= (double)nStructPtr->outputNodeCount;
        
        avgError += calcTmp;
    }
    avgError /= (double)KEEL_GetDataAmount(*traDataPtr);
    
    printf("Average Error: %lf %%\n", avgError);
    
    // Save Info to File
    if(saveState == 0)
    {
        tmpFile = fopen(pathBuf, "w");
        if(tmpFile != NULL)
        {
            fprintf(tmpFile, "Average Error: %lf %%", avgError);
            
            fclose(tmpFile);
        }
    }
    
    // Cleanup
    free(nnTarget);
    free(nnOutput);
    
    return 0;
}