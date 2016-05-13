#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "NNLIB.h"
#include "ActiveFunc.h"
#include "Alloc2DArray.h"
#include "MathProc.h"

#define COM_BUFFER_LEN  512

#define CMD_EXIT_STR            "Exit"
#define CMD_READ_DATASET_STR    "ReadDataSet"
#define CMD_CREATE_NN_STR       "CreateNN"
#define CMD_IMPORT_STR          "Import"
#define CMD_EXPORT_STR          "Export"
#define CMD_S_LEARNING_STR      "SLearning"
#define CMD_PREDICTION_STR      "Prediction"
#define CMD_MANUAL_TEST_STR     "ManualTest"
#define CMD_SHOW_CMDL_STR       "?"

#define CMD_FUNC_ARGLIST    struct NN_STRUCT* nStructPtr,                   \
                            struct TRAIN_DATA* traDataPtr,                  \
                            char* comBuf,                                   \
                            int* nnStatePtr,                                \
                            int* traStatePtr,                               \
                            const char* cmdStr[]

enum CMD_ACTION
{
    CMD_READ_DATASET,
    CMD_CREATE_NN,
    CMD_IMPORT,
    CMD_EXPORT,
    CMD_S_LEARNING,
    CMD_PREDICTION,
    CMD_MANUAL_TEST,
    CMD_EXIT,
    CMD_SHOW_CMDL,
    
    CMD_UNKNOWN
};

//#define DEBUG

int CMD_ReadDataSet(CMD_FUNC_ARGLIST);
int CMD_CreateNN(CMD_FUNC_ARGLIST);
int CMD_Import(CMD_FUNC_ARGLIST);
int CMD_Export(CMD_FUNC_ARGLIST);
int CMD_SLearning(CMD_FUNC_ARGLIST);
int CMD_Prediction(CMD_FUNC_ARGLIST);
int CMD_ManualTest(CMD_FUNC_ARGLIST);
int CMD_Exit(CMD_FUNC_ARGLIST);
int CMD_ShowCMDL(CMD_FUNC_ARGLIST);

int SelectCMDCase(const char* inputBuf, const char* cmdStr[]);
int GetFilePath(char* pathBuf, const char* comBuf, const char* inputMsg);

int NNLIB_Prediction(struct NN_STRUCT* nStructPtr, double* prediction, double* desireOutput);

int main(int argc, char* argv[])
{
    int iResult;
    int nnCreateState = 0;
    int trCreateState = 0;
    int exitProgram = 0;
    
    char inputBuf[COM_BUFFER_LEN] = {0};
    char comBuf[COM_BUFFER_LEN] = {0};
    
    struct NN_STRUCT nnData;
    struct TRAIN_DATA trainData;
    
    int (*cmdFunc[CMD_UNKNOWN])(CMD_FUNC_ARGLIST);
    
    const char* cmdStr[CMD_UNKNOWN];
    
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
    
    while(exitProgram == 0)
    {
        // Get Command Line
        printf("\nNNLIB> ");
        scanf(" %512[^\n]s]", inputBuf);
        //fflush(stdin);
        
        // Select Case
        iResult = SelectCMDCase(inputBuf, cmdStr);
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
    }
    
    if(nnCreateState == 1)
    {
        NNLIB_Delete(&nnData);
    }
    
    if(trCreateState == 1)
    {
        NNLIB_DeleteTrainingData(&trainData);
    }
    
    #ifdef DEBUG
    system("pause");
    #endif
    
    return 0;
}

int SelectCMDCase(const char* inputBuf, const char* cmdStr[])
{
    int i, j;
    int caseSelected = CMD_UNKNOWN;
    
    char procBuffer[COM_BUFFER_LEN] = {0};
    char comBuf[COM_BUFFER_LEN] = {0};
    
    strcpy(procBuffer, inputBuf);
    i = 0;
    while(procBuffer[i] != ':' && procBuffer[i] != '\0')
    {
        procBuffer[i] = toupper(procBuffer[i]);
        i++;
    }
    
    for(i = 0; i < CMD_UNKNOWN; i++)
    {
        strcpy(comBuf, cmdStr[i]);
        
//        #ifdef DEBUG
//        printf("cmdStr = %s\n", cmdStr[i]);
//        #endif
        
        j = 0;
        while(comBuf[j] != ':' && comBuf[j] != '\0')
        {
            comBuf[j] = toupper(comBuf[j]);
            j++;
        }
        
//        #ifdef DEBUG
//        printf("comBuf = %s\n", comBuf);
//        printf("procBuffer = %s\n", procBuffer);
//        #endif
        
        if(!strncmp(comBuf, procBuffer, strlen(comBuf)))
        {
            caseSelected = i;
            break;
        }
    }
    
    return caseSelected;
}

int CMD_ShowCMDL(CMD_FUNC_ARGLIST)
{
    int i;
    
    printf("=== Command List ===\n");
    for(i = 0; i < CMD_UNKNOWN; i++)
    {
        printf("%s\n", cmdStr[i]);
    }
    
    return 0;
}

int CMD_ManualTest(CMD_FUNC_ARGLIST)
{
    int i;
    
    double* nnInput = NULL;
    double* nnOutput = NULL;
    
    // Memory Allocation
    nnInput = (double*)calloc(nStructPtr->inputNodeCount, sizeof(double));
    if(nnInput == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return -1;
    }
    
    nnOutput = (double*)calloc(nStructPtr->outputNodeCount, sizeof(double));
    if(nnOutput == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnInput);
        return -1;
    }
    
    // Checking
    if(*nnStatePtr != 1)
    {
        printf("No neural networks created!\n");
        free(nnInput);
        free(nnOutput);
        return -1;
    }
    while(1)
    {
        printf("Press ESC to exit or other keys to Test the Neural Networks...");
        if(getch() == 27)
        {
            printf("\n");
            break;
        }
        else
        {
            printf("\n");
        }
        
        // Input Test Data
        for(i = 0; i < nStructPtr->inputNodeCount; i++)
        {
            printf("Assign %d of %d input: ", i + 1, nStructPtr->inputNodeCount);
            scanf("%lf", &nnInput[i]);
        }
        
        NNLIB_ForwardComputation(nStructPtr, nnInput, nnOutput);
        
        printf("Neural Network Output: ");
        for(i = 0; i < nStructPtr->outputNodeCount; i++)
        {
            printf("%lf", nnOutput[i]);
            
            if(i == nStructPtr->outputNodeCount - 1)
            {
                printf("\n\n");
            }
            else
            {
                printf(", ");
            }
        }
    }
    
    //fflush(stdin);
    
    // Cleanup
    free(nnInput);
    free(nnOutput);
    
    return 0;
}

int CMD_Prediction(CMD_FUNC_ARGLIST)
{
    int i, j;
    int correctCount;
    int saveState;
    
    double calcTmp;
    
    double** nnOutput;
    double** nnTarget;
    
    char pathBuf[COM_BUFFER_LEN] = {0};
    
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
    saveState = GetFilePath(pathBuf, comBuf, NULL);
    
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
        correctCount += NNLIB_Prediction(nStructPtr, nnOutput[i], nnTarget[i]);
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
    
    char pathBuf[COM_BUFFER_LEN] = {0};
    
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
    else if(traDataPtr->inputs != nStructPtr->inputNodeCount || traDataPtr->outputs != nStructPtr->outputNodeCount)
    {
        printf("Training dataset is not suitable for current neural networks!\n");
        return -1;
    }
    
    // Get Buffer Info
    sscanf(comBuf, "%*[^-] - %d - %d - %lf : %*s", &dataPerAdjust, &iterCount, &learningRate);
    
    // Determine Data Amounts per Once Adjust
    if(dataPerAdjust <= 0)
    {
        printf("Total %d data, assign Data per Adjusting: ", traDataPtr->dataAmount);
        scanf(" %d", &dataPerAdjust);
        //fflush(stdin);
    }
    
    // Assign Iteration Count
    if(iterCount <= 0)
    {
        printf("Assign Iteration Count: ");
        scanf(" %d", &iterCount);
        //fflush(stdin);
    }
    
    // Assign Learning Rate
    if(learningRate <= 0)
    {
        printf("Assign Learning Rate: ");
        scanf(" %lf", &learningRate);
        //fflush(stdin);
    }
    nStructPtr->learningRate = learningRate;
    
    // Get File Path
    GetFilePath(pathBuf, comBuf, "Error Log Path: ");
    
    #ifdef DEBUG
    printf("dataPerAdjust: %d\n", dataPerAdjust);
    printf("iterCount: %d\n", iterCount);
    printf("learningRate: %lf\n", learningRate);
    printf("Error Log Path: %s\n", pathBuf);
    #endif
    
    // Total Process Data
    procTotal = iterCount * traDataPtr->dataAmount;
    
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
        tmpTraIndex = i % traDataPtr->dataAmount;
        i++;
        
        // Forward Compution
        NNLIB_ForwardComputation(nStructPtr, traDataPtr->trainingData[tmpTraIndex], nnBuffer[dataFed]);
      
        // Copy Target and Output
        for(j = 0; j < nStructPtr->outputNodeCount; j++)
        {
            nnTarget[j][dataFed] = traDataPtr->trainingData[tmpTraIndex][nStructPtr->inputNodeCount + j];
            nnOutput[j][dataFed] = nnBuffer[dataFed][j];
        }
        
        dataFed++;
        
        // If processed data reach dataPerAdjust
        if(dataFed == dataPerAdjust)
        {
            // Find dError
            #ifdef DEBUG
            printf("Error: ");
            #endif
            
            for(j = 0; j < nStructPtr->outputNodeCount; j++)
            {
                errAvg[j] = MLIB_FindMSE_Derivative(nnTarget[j], nnOutput[j], dataFed);
                
                #ifdef DEBUG
                printf("%lf, ", errAvg[j]);
                #endif
            }
            
            #ifdef DEBUG
            printf("\n");
            #endif
            
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
        
        printf("%5.2lf %% \r", (double)i / (double)procTotal * 100.0);
        
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
            for(j = 0; j < traDataPtr->dataAmount; j++)
            {
                savedErrLog[i] += errLog[(i + 1) * j / dataPerAdjust];
            }
            savedErrLog[i] /= (double)traDataPtr->dataAmount;
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

int CMD_Export(CMD_FUNC_ARGLIST)
{
    int iResult;
    char pathBuf[COM_BUFFER_LEN] = {0};
    
    // Get File Path
    GetFilePath(pathBuf, comBuf, "File Path: ");
    
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

int CMD_Import(CMD_FUNC_ARGLIST)
{
    int iResult;
    char pathBuf[COM_BUFFER_LEN] = {0};
    
    // Checking
    if(*nnStatePtr == 1)
    {
        NNLIB_Delete(nStructPtr);
        *nnStatePtr = 0;
    }
    
    // Get File Path
    GetFilePath(pathBuf, comBuf, "File Path: ");
    
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

int CMD_CreateNN(CMD_FUNC_ARGLIST)
{
    int i, iResult;
    
    // Checking
    if(*nnStatePtr == 1)
    {
        NNLIB_Delete(nStructPtr);
        *nnStatePtr = 0;
    }
    
    // Determine Neural Networks Detail
    if(*traStatePtr == 1)
    {
        nStructPtr->inputNodeCount = traDataPtr->inputs;
        nStructPtr->outputNodeCount = traDataPtr->outputs;
    }
    else
    {
        printf("Assign Input Nodes: ");
        scanf(" %d", &nStructPtr->inputNodeCount);
        //fflush(stdin);
        
        printf("Assign Output Nodes: ");
        scanf(" %d", &nStructPtr->outputNodeCount);
        //fflush(stdin);
    }
    
    printf("Assign Hidden Layer Amount: ");
    scanf(" %d", &nStructPtr->layerCount);
    //fflush(stdin);
    
    nStructPtr->nodesEachLayer = (int*)calloc(nStructPtr->layerCount, sizeof(int));
    if(nStructPtr->nodesEachLayer == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return -1;
    }
    
    for(i = 0; i < nStructPtr->layerCount; i++)
    {
        printf("Assign Hidden Layer %d Nodes: ", i);
        scanf(" %d", &nStructPtr->nodesEachLayer[i]);
        //fflush(stdin);
    }
    
    nStructPtr->layerCount += 2;
    
    // Create Neural Networks
    iResult = NNLIB_Create(nStructPtr);
    if(iResult != 0)
    {
        printf("Failed to create neural networks!\n");
        return -1;
    }
    
    // Assign Activation Function
    NNLIB_SetActiveFunc(nStructPtr, NNLIB_ASSIGN_SAME_ACTFUNC, activeFunc_Sigmoidal);
    NNLIB_SetdActiveFunc(nStructPtr, NNLIB_ASSIGN_SAME_ACTFUNC, dActiveFunc_Sigmoidal);
    
    // Rand Weights
    NNLIB_RandWeight(nStructPtr);
    
    *nnStatePtr = 1;
    
    return 0;
}

int CMD_ReadDataSet(CMD_FUNC_ARGLIST)
{
    int iResult;
    char pathBuf[COM_BUFFER_LEN] = {0};
    
    // Checking
    if(*traStatePtr == 1)
    {
        NNLIB_DeleteTrainingData(traDataPtr);
        *traStatePtr = 0;
    }
    
    // Get File Path
    GetFilePath(pathBuf, comBuf, "Dataset Path: ");
    
    #ifdef DEBUG
    printf("File Path: %s\n", pathBuf);
    #endif
    
    // Read Training Data
    iResult = NNLIB_ReadTrainingData(traDataPtr, pathBuf);
    if(iResult != 0)
    {
        printf("Failed to read training data!\n");
        return -1;
    }
    else
    {
        *traStatePtr = 1;
    }
    
    return 0;
}

int GetFilePath(char* pathBuf, const char* comBuf, const char* inputMsg)
{
    int i;
    
    // Find ':'
    i = 0;
    while(comBuf[i] != ':' && comBuf[i] != '\0')
    {
        i++;
    }
    
    // Checking
    if(comBuf[i] != ':')
    {
        if(inputMsg == NULL)
        {
            return -1;
        }
        
        printf("%s", inputMsg);
        scanf(" %512[^\n]s]", pathBuf);
        //fflush(stdin);
    }
    else
    {
        strcpy(pathBuf, &comBuf[i + 1]);
    }
    
    if(pathBuf[strlen(pathBuf) - 1] == '"')
    {
        pathBuf[strlen(pathBuf) - 1] = '\0';
    }
    if(pathBuf[0] == '"')
    {
        memmove((void*)pathBuf, (void*)(&pathBuf[1]), strlen(pathBuf));
    }

    return 0;
}

int NNLIB_Prediction(struct NN_STRUCT* nStructPtr, double* prediction, double* desireOutput)
{
    int i, iResult;
    
    char* tarConvert;
    char* outConvert;
    
    // Memory Allocation
    tarConvert = (char*)calloc(nStructPtr->outputNodeCount + 1, sizeof(char));
    if(tarConvert == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return -1;
    }
    
    outConvert = (char*)calloc(nStructPtr->outputNodeCount + 1, sizeof(char));
    if(outConvert == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(tarConvert);
        return -1;
    }
    
    for(i = 0; i < nStructPtr->outputNodeCount; i++)
    {
        if(desireOutput[i] > 0.75)
        {
            tarConvert[i] = '1';
        }
        else if(desireOutput[i] < 0.25)
        {
            tarConvert[i] = '0';
        }
        else
        {
            free(tarConvert);
            free(outConvert);
            return 0;
        }
        
        if(prediction[i] > 0.75)
        {
            outConvert[i] = '1';
        }
        else if(prediction[i] < 0.25)
        {
            outConvert[i] = '0';
        }
        else
        {
            free(tarConvert);
            free(outConvert);
            return 0;
        }
    }
    
    iResult = (strncmp(tarConvert, outConvert, nStructPtr->outputNodeCount) == 0) ? 1 : 0;
    
    // Cleanup
    free(tarConvert);
    free(outConvert);
    
    return iResult;
}
