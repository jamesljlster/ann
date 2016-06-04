#include <stdio.h>

#include "NNLIB.h"
#include "CMDL.h"

int CMD_ReadDataSet(CMD_FUNC_ARGLIST)
{
//    int i;
    
    char pathBuf[CMD_BUFFER_LEN] = {0};
    
    // Checking
    if(*traStatePtr == 1)
    {
        KEEL_Delete(*traDataPtr);
        *traStatePtr = 0;
    }
    
    // Get File Path
    CMD_GetFilePath(pathBuf, comBuf, "Dataset Path: ");
    
    #ifdef DEBUG
    printf("File Path: %s\n", pathBuf);
    #endif
    
    // Read Training Data
    *traDataPtr = KEEL_ReadDataset(pathBuf);
    if(*traDataPtr == NULL)
    {
        printf("Failed to read training data!\n");
        return -1;
    }
    else
    {
        *traStatePtr = 1;
    }
    
    // Normalization
//    for(i = 0; i < KEEL_GetInputs(*traDataPtr); i++)
//    {
//        KEEL_Normalize(*traDataPtr, i, -1, 1);
//    }

//    if(KEEL_GetOutputs(*traDataPtr) == 1)
//    {
//        KEEL_Normalize(*traDataPtr, KEEL_GetInputs(*traDataPtr), 0, 1);
//        
//        for(i = 0; i < KEEL_GetInputs(*traDataPtr); i++)
//        {
//            KEEL_Normalize(*traDataPtr, i, -1, 1);
//        }
//    }
    
    return 0;
}

int CMD_Import(CMD_FUNC_ARGLIST)
{
    int iResult;
    char pathBuf[CMD_BUFFER_LEN] = {0};
    
    // Checking
    if(*nnStatePtr == 1)
    {
        NNLIB_Delete(nStructPtr);
        *nnStatePtr = 0;
    }
    
    // Get File Path
    CMD_GetFilePath(pathBuf, comBuf, "File Path: ");
    
    #ifdef DEBUG
    printf("File Path: %s\n", pathBuf);
    #endif
    
    // Read Training Data
    iResult = NNLIB_Import(nStructPtr, pathBuf);
    if(iResult != 0)
    {
        printf("Failed to import neural networks!\n");
        return -1;
    }
    else
    {
        *nnStatePtr = 1;
    }
    
    return 0;
}

int CMD_Export(CMD_FUNC_ARGLIST)
{
    int iResult;
    char pathBuf[CMD_BUFFER_LEN] = {0};
    
    // Get File Path
    CMD_GetFilePath(pathBuf, comBuf, "File Path: ");
    
    #ifdef DEBUG
    printf("File Path: %s\n", pathBuf);
    #endif
    
    // Checking
    if(*nnStatePtr == 0)
    {
        printf("No neural networks created!\n");
        return -1;
    }
    
    // Exporting
    iResult = NNLIB_Export(nStructPtr, pathBuf);
    if(iResult != 0)
    {
        printf("Failed to export neural networks!\n");
        return -1;
    }
    
    return 0;
}
