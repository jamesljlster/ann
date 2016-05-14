#include <stdio.h>
#include <stdlib.h>

#include "NNLIB.h"
#include "CMDL.h"
#include "Alloc2DArray.h"

int CMD_Prediction(CMD_FUNC_ARGLIST)
{
    int i, j;
    int correctCount;
    int saveState;
    
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
    else if(traDataPtr->inputs != nStructPtr->inputNodeCount || traDataPtr->outputs != nStructPtr->outputNodeCount)
    {
        printf("Training dataset is not suitable for current neural networks!\n");
        return -1;
    }
    
    // Get File Path
    saveState = CMD_GetFilePath(pathBuf, comBuf, NULL);
    
    // Memory Allocation
    nnOutput = (double**)Alloc2DArray(traDataPtr->dataAmount, nStructPtr->outputNodeCount, sizeof(double));
    if(nnOutput == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return -1;
    }
    
    nnTarget = (double**)Alloc2DArray(traDataPtr->dataAmount, nStructPtr->outputNodeCount, sizeof(double));
    if(nnTarget == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnOutput);
        return -1;
    }
    
    // Iteration
    for(i = 0; i < traDataPtr->dataAmount; i++)
    {
        // Forward Computation
        NNLIB_ForwardComputation(nStructPtr, traDataPtr->trainingData[i], nnOutput[i]);
        
        // Copy Target and Output
        for(j = 0; j < nStructPtr->outputNodeCount; j++)
        {
            nnTarget[i][j] = traDataPtr->trainingData[i][nStructPtr->inputNodeCount + j];
        }
    }
    
    // Find Prediction Correct Rate
    correctCount = 0;
    for(i = 0; i < traDataPtr->dataAmount; i++)
    {
        correctCount += NNLIB_Prediction_Hard(nStructPtr, nnOutput[i], nnTarget[i]);
    }
    
    calcTmp = ((double)correctCount / (double)traDataPtr->dataAmount) * 100.0;
    printf("Prediction Success Rate: %5.2lf %%\n", calcTmp);
    
    // Save Info to File
    if(saveState == 0)
    {
        tmpFile = fopen(pathBuf, "w");
        if(tmpFile != NULL)
        {
            fprintf(tmpFile, "Prediction Result: %lf", calcTmp);
            
            fclose(tmpFile);
        }
    }
    
    // Cleanup
    free(nnTarget);
    free(nnOutput);
    
    return 0;
}
