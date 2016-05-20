#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "NNLIB.h"
#include "CMDL.h"
#include "Alloc2DArray.h"
#include "MathProc.h"

int CMD_SLearning(CMD_FUNC_ARGLIST)
{
    int i, j;
    int tmpTraIndex;
    int dataFed;
    int csvLineIndex;
    int iterCount;
    int procTotal;
    int dataPerAdjust = -1;
    int stopLearning = 0;
    
    char pathBuf[CMD_BUFFER_LEN] = {0};
    
    double learningRate;
    double calcTmp;
    
    double* errLog = NULL;
    double* errAvg = NULL;
    double* savedErrLog = NULL;
    double** nnBuffer = NULL;
    double** nnTarget = NULL;
    double** nnOutput = NULL;
    
    clock_t timeHold;
    
    FILE* tmpFile;
    
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
    
    // Get Buffer Info
    sscanf(comBuf, "%*[^-] - %d - %d - %lf : %*s", &dataPerAdjust, &iterCount, &learningRate);
    
    // Determine Data Amounts per Once Adjust
    if(dataPerAdjust <= 0)
    {
        printf("Total %d data, assign Data per Adjusting: ", KEEL_GetDataAmount(*traDataPtr));
        scanf(" %d", &dataPerAdjust);
    }
    
    // Assign Iteration Count
    if(iterCount <= 0)
    {
        printf("Assign Iteration Count: ");
        scanf(" %d", &iterCount);
    }
    
    // Assign Learning Rate
    if(learningRate <= 0)
    {
        printf("Assign Learning Rate: ");
        scanf(" %lf", &learningRate);
    }
    nStructPtr->learningRate = learningRate;
    
    // Get File Path
    CMD_GetFilePath(pathBuf, comBuf, "Error Log Path: ");
    
    #ifdef DEBUG
    printf("dataPerAdjust: %d\n", dataPerAdjust);
    printf("iterCount: %d\n", iterCount);
    printf("learningRate: %lf\n", learningRate);
    printf("Error Log Path: %s\n", pathBuf);
    #endif
    
    // Total Process Data
    procTotal = iterCount * KEEL_GetDataAmount(*traDataPtr);
    
    // Memory Allocation
    nnBuffer = (double**)Alloc2DArray(dataPerAdjust, nStructPtr->outputNodeCount, sizeof(double));
    if(nnBuffer == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return -1;
    }
    
    nnTarget = (double**)Alloc2DArray(nStructPtr->outputNodeCount, dataPerAdjust, sizeof(double));
    if(nnTarget == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnBuffer);
        return -1;
    }
    
    nnOutput = (double**)Alloc2DArray(nStructPtr->outputNodeCount, dataPerAdjust, sizeof(double));
    if(nnOutput == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnBuffer);
        free(nnTarget);
        return -1;
    }
    
    errAvg = (double*)calloc(nStructPtr->outputNodeCount, sizeof(double));
    if(errAvg == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnBuffer);
        free(nnTarget);
        free(nnOutput);
        return -1;
    }
    
    savedErrLog = (double*)calloc(iterCount, sizeof(double));
    if(savedErrLog == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnBuffer);
        free(nnTarget);
        free(nnOutput);
        free(errAvg);
        return -1;
    }
    
    i = (procTotal % dataPerAdjust == 0) ? (procTotal / dataPerAdjust) : (procTotal / dataPerAdjust) + 1;
    errLog = (double*)calloc(i, sizeof(double));
    if(errLog == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnBuffer);
        free(nnTarget);
        free(nnOutput);
        free(errAvg);
        free(savedErrLog);
        return -1;
    }
    
    stopLearning = 0;
    dataFed = 0;
    i = 0;
    csvLineIndex = 0;
    timeHold = clock();
    while(i < procTotal && stopLearning == 0)
    {
        tmpTraIndex = i % KEEL_GetDataAmount(*traDataPtr);
        i++;
        
        // Forward Compution
        NNLIB_ForwardComputation(nStructPtr, KEEL_GetInputList(*traDataPtr, tmpTraIndex), nnBuffer[dataFed]);
      
        // Copy Target and Output
        for(j = 0; j < nStructPtr->outputNodeCount; j++)
        {
            nnTarget[j][dataFed] = KEEL_GetOutputList(*traDataPtr, tmpTraIndex)[j];
            nnOutput[j][dataFed] = nnBuffer[dataFed][j];
        }
        
        dataFed++;
        
        // If processed data reach dataPerAdjust
        if(dataFed == dataPerAdjust)
        {
            // Find dError
//            #ifdef DEBUG
//            printf("Error: ");
//            #endif
            
            for(j = 0; j < nStructPtr->outputNodeCount; j++)
            {
                errAvg[j] = MLIB_FindMSE_Derivative(nnTarget[j], nnOutput[j], dataFed);
                
//                #ifdef DEBUG
//                printf("%lf, ", errAvg[j]);
//                #endif
            }
            
//            #ifdef DEBUG
//            printf("\n");
//            #endif
            
            // Back-Propagation
            NNLIB_BackPropagation_Gradient(nStructPtr, learningRate, errAvg);
            
            // Find Error
            calcTmp = 0;
            for(j = 0; j < nStructPtr->outputNodeCount; j++)
            {
                calcTmp += MLIB_FindMSE(nnTarget[j], nnOutput[j], dataFed);
            }
            errLog[csvLineIndex] = calcTmp / (double)nStructPtr->outputNodeCount;
            
            csvLineIndex++;
            
            dataFed = 0;
        }
        else if(i == procTotal)
        {
            // Find dError
            for(j = 0; j < nStructPtr->outputNodeCount; j++)
            {
                errAvg[j] = MLIB_FindMSE_Derivative(nnTarget[j], nnOutput[j], dataFed);
            }
            
            // Back-Propagation
            NNLIB_BackPropagation_Gradient(nStructPtr, learningRate, errAvg);
            
            // Find MSE
            calcTmp = 0;
            for(j = 0; j < nStructPtr->outputNodeCount; j++)
            {
                calcTmp += MLIB_FindMSE(nnTarget[j], nnOutput[j], dataFed);
            }
            errLog[csvLineIndex++] = calcTmp / (double)nStructPtr->outputNodeCount;
        }
        
        printf(" [ %5.2lf %% ] \r", (double)i / (double)procTotal * 100.0);
        
        if(kbhit())
        {
            if(getch() == 27)
            {
                stopLearning = 1;
            }
        }
    }
    
    // Calculate Processing Time
    timeHold = clock() - timeHold;
    calcTmp = (double)timeHold / (double)CLOCKS_PER_SEC;
    
    printf("Time Cost: %lf\n", calcTmp);
    
    tmpFile = fopen(pathBuf, "w");
    if(tmpFile != NULL && stopLearning == 0)
    {
        // Process Error Log
        for(i = 0; i < iterCount; i++)
        {
            savedErrLog[i] = 0;
            for(j = 0; j < KEEL_GetDataAmount(*traDataPtr); j++)
            {
                savedErrLog[i] += errLog[(i + 1) * j / dataPerAdjust];
            }
            savedErrLog[i] /= (double)KEEL_GetDataAmount(*traDataPtr);
        }
        
        fprintf(tmpFile, "MSE, Time Cost: %lf s\n", calcTmp);
        
        for(i = 0; i < iterCount; i++)
        {
            fprintf(tmpFile, "%lf\n", savedErrLog[i]);
        }
        
        fclose(tmpFile);
    }
    
    // Cleanup
    free(nnBuffer);
    free(nnTarget);
    free(nnOutput);
    free(errLog);
    free(savedErrLog);
    
    return 0;
}
