#include <stdlib.h>

#include "KEEL_DataProc.h"

//#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif // DEBUG

int KEEL_Normalize(KEEL_DATA keelData, int targetColumn, double targetMin, double targetMax)
{
    int i;

    double dataMin, dataMax;

    // Find Max and Min Value
    dataMin = keelData->data[targetColumn];
    dataMax = keelData->data[targetColumn];
    for(i = 1; i < keelData->dataRows; i++)
    {
        if(dataMax < keelData->data[i * keelData->dataCols + targetColumn]) dataMax = keelData->data[i * keelData->dataCols + targetColumn];
        if(dataMin > keelData->data[i * keelData->dataCols + targetColumn]) dataMin = keelData->data[i * keelData->dataCols + targetColumn];
    }

    #ifdef DEBUG
    printf("dataMax = %lf, dataMin = %lf\n", dataMax, dataMin);
    #endif // DEBUG

    // Normalization
    for(i = 0; i < keelData->dataRows; i++)
    {
        keelData->data[i * keelData->dataCols + targetColumn] = (keelData->data[i * keelData->dataCols + targetColumn] - dataMin) / (dataMax - dataMin) + targetMin;
    }

    return 0;
}

int KEEL_Delete(KEEL_DATA keelData)
{
    int i, j;

    // Free Attribute
    for(i = 0; i < keelData->attrAmount; i++)
    {
        // Free Attribute Name
        free(keelData->attrList[i].attrName);

        // Free Attribute Type
        if(keelData->attrList[i].attrType != NULL)
        {
            free(keelData->attrList[i].attrType);
        }

        // Free Attribute Member
        for(j = 0; j < keelData->attrList[i].memberCount; j++)
        {
            free(keelData->attrList[i].member[j]);
        }
        free(keelData->attrList[i].member);
    }
    free(keelData->attrList);

    // Free Data
    free(keelData->data);
    free(keelData->inputAttrIndexList);
    free(keelData->name);

    // Free KEEL_DATA
    free(keelData);

    return 0;
}

int KEEL_GetDataAmount(KEEL_DATA keelData)
{
    return keelData->dataRows;
}

int KEEL_GetInputs(KEEL_DATA keelData)
{
    return keelData->inputs;
}

int KEEL_GetOutputs(KEEL_DATA keelData)
{
    return keelData->outputs;
}

double* KEEL_GetInputList(KEEL_DATA keelData, int dataIndex)
{
    return &(keelData->data[dataIndex * keelData->dataCols]);
}

double* KEEL_GetOutputList(KEEL_DATA keelData, int dataIndex)
{
    return &(keelData->data[dataIndex * keelData->dataCols + keelData->inputs]);
}
