#include <stdio.h>
#include <stdlib.h>

#include "NNLIB.h"
#include "CMDL.h"
#include "Alloc2DArray.h"

//#define DEBUG

int CMDL_Denormalize(double** target, int targetColumn, int length, double minValue, double maxValue);

int CMD_GetOutput(CMD_FUNC_ARGLIST)
{
    int i, j;
    
    double** nnOutput;
    double** nnTarget;
    
    double deNormMin;
    double deNormMax;
    
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
    CMD_GetFilePath(pathBuf, comBuf, "Output File Path: ");
    
    // Create File
    tmpFile = fopen(pathBuf, "w");
    if(tmpFile == NULL)
    {
        printf("Failed to create %s !\n", pathBuf);
        
        return 0;
    }
    
    // Memory Allocation
    nnOutput = (double**)Alloc2DArray(KEEL_GetDataAmount(*traDataPtr), nStructPtr->outputNodeCount, sizeof(double));
    if(nnOutput == NULL)
    {
        printf("Memory Allocation Failed!\n");
        fclose(tmpFile);
        return -1;
    }
    
    nnTarget = (double**)Alloc2DArray(KEEL_GetDataAmount(*traDataPtr), nStructPtr->outputNodeCount, sizeof(double));
    if(nnTarget == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnOutput);
        fclose(tmpFile);
        return -1;
    }
    
    // Forward Compution
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
    
    // Recover Normalized Data
    if(KEEL_GetOutputs(*traDataPtr) == 1)
    {
        deNormMin = atof((*traDataPtr)->attrList[KEEL_GetInputs(*traDataPtr)].member[0]);
        deNormMax = atof((*traDataPtr)->attrList[KEEL_GetInputs(*traDataPtr)].member[1]);
        
        CMDL_Denormalize(nnTarget, 0, KEEL_GetDataAmount(*traDataPtr), deNormMin, deNormMax);
        CMDL_Denormalize(nnOutput, 0, KEEL_GetDataAmount(*traDataPtr), deNormMin, deNormMax);
    }
    
    // Write File
    fprintf(tmpFile, "# ");
    for(i = 0; i < nStructPtr->outputNodeCount; i++)
    {
        fprintf(tmpFile, "RealOutput-%d, DesireOutput-%d", i, i);
        
        if(i == nStructPtr->outputNodeCount - 1)
        {
            fprintf(tmpFile, "\n");
        }
        else
        {
            fprintf(tmpFile, ", ");
        }
    }
    
    for(i = 0; i < KEEL_GetDataAmount(*traDataPtr); i++)
    {
        for(j = 0; j < nStructPtr->outputNodeCount; j++)
        {
            fprintf(tmpFile, "%lf, %lf", nnOutput[i][j], nnTarget[i][j]);
            
            if(j == nStructPtr->outputNodeCount - 1)
            {
                fprintf(tmpFile, "\n");
            }
            else
            {
                fprintf(tmpFile, ", ");
            }
        }
    }
    
    fclose(tmpFile);
    
    return 0;
}

int CMDL_Denormalize(double** target, int targetColumn, int length, double minValue, double maxValue)
{
    int i;

    double dataMin, dataMax;

    // Find Max and Min Value
    dataMin = target[0][targetColumn];
    dataMax = target[0][targetColumn];
    for(i = 1; i < length; i++)
    {
        if(dataMax < target[i][targetColumn]) dataMax = target[i][targetColumn];
        if(dataMin > target[i][targetColumn]) dataMin = target[i][targetColumn];
    }

    #ifdef DEBUG
    printf("dataMax = %lf, dataMin = %lf\n", dataMax, dataMin);
    #endif // DEBUG

    // Denormalization
    for(i = 0; i < length; i++)
    {
        target[i][targetColumn] = ((target[i][targetColumn] - dataMin) / (dataMax - dataMin)) * (maxValue - minValue) + minValue;
    }

    return 0;
}
