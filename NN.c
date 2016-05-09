#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "NNLIB.h"

int NNLIB_readConing (struct NN_STRUCT* nStructPtr, char* NNConfig)
{
    int count=0;
    int hiddenLayerCount;
    FILE *NNSetting;

    NNSetting=fopen(NNConfig,"r");
    
    fscanf(NNSetting, "LearningRate = %lf\n", &nStructPtr->learningRate);
    fscanf(NNSetting,"Input = %d\n",&nStructPtr->inputNodeCount);
    fscanf(NNSetting,"Layer = %d\n",&hiddenLayerCount);
    nStructPtr->layerCount=hiddenLayerCount+2;
    fscanf(NNSetting,"Output = %d\n",&nStructPtr->outputNodeCount);
    printf("Input = %d\nLayer = %d\nOutput = %d\n",nStructPtr->inputNodeCount,nStructPtr->layerCount,nStructPtr->outputNodeCount);
    fscanf(NNSetting,"Node = ");

    nStructPtr->nodesEachLayer=calloc(nStructPtr->layerCount, sizeof(int));
    for(count=0; count < hiddenLayerCount; count++)
    {
        fscanf(NNSetting,"%d ",&nStructPtr->nodesEachLayer[count]);
        printf("Layer%d has %d nodes\n", count, nStructPtr->nodesEachLayer[count]);
    }
    fclose(NNSetting);
    return 0;

}
