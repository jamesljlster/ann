#include <stdio.h>
#include <stdlib.h>

#include "NNLIB.h"
#include "ActiveFunc.h"

//#define DEBUG

int NNLIB_Import(struct NN_STRUCT* nStructPtr, const char* filePath)
{
    int iResult;
    int i, j, k;
    
    FILE* fileRead;
    
    struct NN_LAYER* nLayerRef = NULL;
    
    // Open File
    fileRead = fopen(filePath, "r");
    if(fileRead == NULL)
    {
        return -1;
    }
    
    // Import Neural Network Details
    fscanf(fileRead, "LearningRate: %lf\n", &nStructPtr->learningRate);
    fscanf(fileRead, "Input: %d\n", &nStructPtr->inputNodeCount);
    fscanf(fileRead, "Output: %d\n", &nStructPtr->outputNodeCount);
    fscanf(fileRead, "LayerCount: %d\n", &nStructPtr->layerCount);
    
    if(nStructPtr->layerCount > 2)
    {
        // Memory Allocation: Node count of each hidden layer
        nStructPtr->nodesEachLayer = (int*)calloc(nStructPtr->layerCount - 2, sizeof(int));
        if(nStructPtr->nodesEachLayer == NULL)
        {
            fclose(fileRead);
            return -1;
        }
        
        fscanf(fileRead, "HiddenNodes: ");
        for(i = 0; i < nStructPtr->layerCount - 2; i++)
        {
            fscanf(fileRead, "%d", &nStructPtr->nodesEachLayer[i]);
            
            if(i == nStructPtr->layerCount - 3)
            {
                fscanf(fileRead, "\n");
            }
            else
            {
                fscanf(fileRead, ", ");
            }
        }
    }
    
    #ifdef DEBUG
    
    printf("LearningRate: %lf\n", nStructPtr->learningRate);
    printf("Input: %d\n", nStructPtr->inputNodeCount);
    printf("Output: %d\n", nStructPtr->outputNodeCount);
    printf("LayerCount: %d\n", nStructPtr->layerCount);
    for(i = 0; i < nStructPtr->layerCount - 2; i++)
    {
        printf("Hidden Layer %d has %d nodes\n", i, nStructPtr->nodesEachLayer[i]);
    }
    
    #endif
    
    // Create Neural Network
    iResult = NNLIB_Create(nStructPtr);
    if(iResult != 0)
    {
        free(nStructPtr->nodesEachLayer);
        fclose(fileRead);
        return -1;
    }
    
    // Import Weight and Threshold in nodes
    nLayerRef = nStructPtr->nLayerHandle;
    for(i=1; i<nStructPtr->layerCount; i++)
    {
        for(j=0; j<nLayerRef[i - 1].nodeCount; j++)
        {
            for(k=0; k<nLayerRef[i].nodeCount; k++)
            {
                fscanf(fileRead, "%lf", &nLayerRef[i].nodeList[k].weight[j]);
                
                if(k == nLayerRef[i].nodeCount - 1)
                {
                    fscanf(fileRead, "\n");
                }
                else
                {
                    fscanf(fileRead, ", ");
                }
            }
        }
        
        fscanf(fileRead, "\n");
        for(j=0; j<nLayerRef[i].nodeCount; j++)
        {
            fscanf(fileRead, "%lf", &nLayerRef[i].nodeList[j].threshold);
            
            if(j == nLayerRef[i].nodeCount - 1)
            {
                fscanf(fileRead, "\n");
            }
            else
            {
                fscanf(fileRead, ", ");
            }
        }
        fscanf(fileRead, "\n");
    }
    
    fclose(fileRead);
    
    // Set Activation Function
    NNLIB_SetActiveFunc(nStructPtr, NNLIB_ASSIGN_SAME_ACTFUNC, activeFunc_Sigmoidal);
    NNLIB_SetdActiveFunc(nStructPtr, NNLIB_ASSIGN_SAME_ACTFUNC, dActiveFunc_Sigmoidal);
    
    return 0;
}

int NNLIB_Export(struct NN_STRUCT* nStructPtr, const char* filePath)
{
    int i, j, k;
    
    FILE* fileWrite;
    
    struct NN_LAYER* nLayerRef = nStructPtr->nLayerHandle;
    
    // Create write file
    fileWrite = fopen(filePath, "w");
    if(fileWrite == NULL)
    {
        return -1;
    }
    
    // Export Neural Network Details
    fprintf(fileWrite, "LearningRate: %lf\n", nStructPtr->learningRate);
    fprintf(fileWrite, "Input: %d\n", nStructPtr->inputNodeCount);
    fprintf(fileWrite, "Output: %d\n", nStructPtr->outputNodeCount);
    fprintf(fileWrite, "LayerCount: %d\n", nStructPtr->layerCount);
    fprintf(fileWrite, "HiddenNodes: ");
    for(i = 0; i < nStructPtr->layerCount - 2; i++)
    {
        fprintf(fileWrite, "%d", nStructPtr->nodesEachLayer[i]);
        
        if(i == nStructPtr->layerCount - 3)
        {
            fprintf(fileWrite, "\n");
        }
        else
        {
            fprintf(fileWrite, ", ");
        }
    }
    
    // Export Weight and Threshold in nodes
    for(i=1; i<nStructPtr->layerCount; i++)
    {
        for(j=0; j<nLayerRef[i - 1].nodeCount; j++)
        {
            for(k=0; k<nLayerRef[i].nodeCount; k++)
            {
                fprintf(fileWrite, "%+lf", nLayerRef[i].nodeList[k].weight[j]);
                
                if(k == nLayerRef[i].nodeCount - 1)
                {
                    fprintf(fileWrite, "\n");
                }
                else
                {
                    fprintf(fileWrite, ", ");
                }
            }
        }
        
        fprintf(fileWrite, "\n");
        for(j=0; j<nLayerRef[i].nodeCount; j++)
        {
            fprintf(fileWrite, "%+lf", nLayerRef[i].nodeList[j].threshold);
            
            if(j == nLayerRef[i].nodeCount - 1)
            {
                fprintf(fileWrite, "\n");
            }
            else
            {
                fprintf(fileWrite, ", ");
            }
        }
        fprintf(fileWrite, "\n");
    }
    
    fclose(fileWrite);
    
    return 0;
}