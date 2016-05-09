#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Alloc2DArray.h"
#include "NNLIB.h"

int NNLIB_DeleteTrainingData(struct TRAIN_DATA* trainDataPtr)
{
    free(trainDataPtr->trainingData);
    
    return 0;
}

int NNLIB_ReadTrainingData(struct TRAIN_DATA* trainDataPtr, const char* dataPath)
{
    int i, iResult;
    int dataCols;
    int dataAmount = 0;
    
    double* tmpPtr = NULL;
    double* dataTmp = NULL;
    
    FILE* dataRead = NULL;
    
    // Open Training Data
    dataRead = fopen(dataPath, "r");
    if(dataRead == NULL)
    {
        return -1;
    }
    
    // Read Training Data
    fscanf(dataRead, "Input: %d\n", &trainDataPtr->inputs);
    fscanf(dataRead, "Output: %d\n", &trainDataPtr->outputs);
    
    dataCols = trainDataPtr->inputs + trainDataPtr->outputs;
    
    while(!feof(dataRead))
    {
        dataAmount++;
        tmpPtr = (double*)realloc(dataTmp, dataCols * dataAmount * sizeof(double));
        if(tmpPtr == NULL)
        {
            free(dataTmp);
            fclose(dataRead);
            return -1;
        }
        else
        {
            dataTmp = tmpPtr;
        }
        
        for(i=0; i<dataCols; i++)
        {
            iResult = fscanf(dataRead, "%lf", &(dataTmp[(dataAmount - 1) * dataCols + i]));
            if(iResult <= 0)
            {
                dataAmount--;
                break;
            }
            
            if(i == dataCols - 1)
            {
                fscanf(dataRead, " \n");
            }
            else
            {
                fscanf(dataRead, " , ");
            }
        }
    }
    
    // Close File
    fclose(dataRead);
    
    // Memory Allocation: Training Data
    trainDataPtr->trainingData = (double**)Alloc2DArray(dataAmount, dataCols, sizeof(double));
    if(trainDataPtr->trainingData == NULL)
    {
        free(dataTmp);
        return -1;
    }
    
    // Setting Values
    trainDataPtr->dataAmount = dataAmount;
    trainDataPtr->cols = dataCols;
    memcpy((void*)&((trainDataPtr->trainingData)[0][0]), (void*)dataTmp, dataAmount * dataCols * sizeof(double));
    
    free(dataTmp);
    
    return 0;
}