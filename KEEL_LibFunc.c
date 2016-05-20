#include <stdlib.h>

#include "KEEL_DataProc.h"

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
