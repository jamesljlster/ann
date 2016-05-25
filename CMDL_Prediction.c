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
//            nnTarget[i][j] = traDataPtr->trainingData[i][nStructPtr->inputNodeCount + j];
        }
    }
    
    // Find Prediction Correct Rate
    correctCount = 0;
    for(i = 0; i < KEEL_GetDataAmount(*traDataPtr); i++)
    {
//        correctCount += NNLIB_Prediction_Hard(nStructPtr, nnOutput[i], nnTarget[i]);
        correctCount += NNLIB_Prediction_Soft(nStructPtr, nnOutput[i], nnTarget[i]);
    }
    
    calcTmp = ((double)correctCount / (double)KEEL_GetDataAmount(*traDataPtr)) * 100.0;
    printf("Prediction Successful Rate: %5.2lf %%\n", calcTmp);
    
    // Save Info to File
    if(saveState == 0)
    {
        tmpFile = fopen(pathBuf, "w");
        if(tmpFile != NULL)
        {
            fprintf(tmpFile, "Prediction Result: %lf %%", calcTmp);
            
            fclose(tmpFile);
        }
    }
    
    // Cleanup
    free(nnTarget);
    free(nnOutput);
    
    return 0;
}
