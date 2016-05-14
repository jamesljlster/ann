#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "NNLIB.h"
#include "CMDL.h"

//#define DEBUG

int main(int argc, char* argv[])
{
    int iResult;
    int nnCreateState = 0;
    int trCreateState = 0;
    int exitProgram = 0;
    
    char inputBuf[CMD_BUFFER_LEN] = {0};
    char pathBuf[CMD_BUFFER_LEN] = {0};
    char comBuf[CMD_BUFFER_LEN] = {0};
    
    struct NN_STRUCT nnData;
    struct TRAIN_DATA trainData;
    
    int (*cmdFunc[CMD_UNKNOWN])(CMD_FUNC_ARGLIST);
    
    const char* cmdStr[CMD_UNKNOWN];
    
    FILE* scriptFile = NULL;
    
    cmdFunc[CMD_EXIT] = NULL;
    cmdFunc[CMD_SHOW_CMDL] = CMD_ShowCMDL;
    cmdFunc[CMD_READ_DATASET] = CMD_ReadDataSet;
    cmdFunc[CMD_CREATE_NN] = CMD_CreateNN;
    cmdFunc[CMD_IMPORT] = CMD_Import;
    cmdFunc[CMD_EXPORT] = CMD_Export;
    cmdFunc[CMD_S_LEARNING] = CMD_SLearning;
    cmdFunc[CMD_PREDICTION] = CMD_Prediction;
    cmdFunc[CMD_MANUAL_TEST] = CMD_ManualTest;
    
    cmdStr[CMD_EXIT] = CMD_EXIT_STR;
    cmdStr[CMD_SHOW_CMDL] = CMD_SHOW_CMDL_STR;
    cmdStr[CMD_READ_DATASET] = CMD_READ_DATASET_STR;
    cmdStr[CMD_CREATE_NN] = CMD_CREATE_NN_STR;
    cmdStr[CMD_IMPORT] = CMD_IMPORT_STR;
    cmdStr[CMD_EXPORT] = CMD_EXPORT_STR;
    cmdStr[CMD_S_LEARNING] = CMD_S_LEARNING_STR;
    cmdStr[CMD_PREDICTION] = CMD_PREDICTION_STR;
    cmdStr[CMD_MANUAL_TEST] = CMD_MANUAL_TEST_STR;

    srand(time(NULL));
    
    // Process main argument
    if(argc > 1)
    {
        iResult = strncmp("-s", argv[1], strlen("-s"));
        if(iResult == 0)
        {
            iResult = CMD_GetFilePath(pathBuf, argv[1], NULL);
            if(iResult == 0)
            {
                scriptFile = fopen(pathBuf, "r");
                if(scriptFile == NULL)
                {
                    printf("Failed to read script file: %s\n", pathBuf);
                    
                    return -1;
                }
            }
        }
        else
        {
            printf("\n");
            printf("Use the following syntax to run NNLIB with script file:\n");
            printf("NNLIB.exe -s:<path_to_script_file>");
            printf("\n");
            
            return -1;
        }
    }
    
    while(exitProgram == 0)
    {
        // Get Command Line
        if(scriptFile != NULL)
        {
            if(!feof(scriptFile))
            {
                fscanf(scriptFile, " %512[^\n]s\n", inputBuf);
                
                #ifdef DEBUG
                printf("Script: %s\n", inputBuf);
                #endif
            }
        }
        
        if(strlen(inputBuf) == 0)
        {
            printf("\nNNLIB> ");
            scanf(" %512[^\n]s]", inputBuf);
        }
        
        // Select Case
        iResult = CMD_SelectCase(inputBuf, cmdStr);
        if(iResult == CMD_UNKNOWN)
        {
            printf("Unknown Command Line: %s\n", inputBuf);
        }
        else if(iResult == CMD_EXIT)
        {
            printf("Exit NNLIB...\n");
            exitProgram = 1;
        }
        else
        {
            strcpy(comBuf, inputBuf);
            cmdFunc[iResult](&nnData, &trainData, comBuf, &nnCreateState, &trCreateState, cmdStr);
        }
        
        // Clear Buffer
        memset((void*)inputBuf, 0, CMD_BUFFER_LEN);
    }
    
    if(nnCreateState == 1)
    {
        NNLIB_Delete(&nnData);
    }
    
    if(trCreateState == 1)
    {
        NNLIB_DeleteTrainingData(&trainData);
    }
    
    if(scriptFile != NULL)
    {
        fclose(scriptFile);
    }
    
    #ifdef DEBUG
    system("pause");
    #endif
    
    return 0;
}
