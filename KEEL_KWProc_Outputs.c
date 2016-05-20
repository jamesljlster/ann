#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "KEEL_DataProc.h"
#include "KEEL_PrivateFunc.h"

//#define DEBUG

int KEEL_KWProc_Outputs(KEEL_DATA keelData, char* fileBuffer, const char* keyword)
{
    int i, iResult;
    int selIndex;
    int procIndex;

    char procBuffer[KEEL_BUFFER_LEN] = {0};
    char scanFormat[KEEL_BUFFER_LEN] = {0};
    char tempBuffer[KEEL_BUFFER_LEN] = {0};

    // Find Output List
    procIndex = KEEL_FindChar(fileBuffer, 0, ' ', KEEL_BUFFER_LEN);
    if(procIndex == -1)
    {
        #ifdef DEBUG
        printf("Unexpected File Format!\n");
        #endif // DEBUG

        return -1;
    }
    else
    {
        procIndex++;
        strcpy(procBuffer, &fileBuffer[procIndex]);
    }

    #ifdef DEBUG
    printf("ProcBuffer: %s\n", procBuffer);
    #endif // DEBUG

    // Get String on List
    sprintf(scanFormat, " %%[^,]s ");
    sscanf(procBuffer, scanFormat, tempBuffer);

    #ifdef DEBUG
    printf("tempBuffer: %s\n", tempBuffer);
    #endif // DEBUG

    selIndex = -1;
    for(i = 0; i < keelData->attrAmount; i++)
    {
        iResult = strncmp(keelData->attrList[i].attrName, tempBuffer, strlen(keelData->attrList[i].attrName));
        if(iResult == 0)
        {
            selIndex = i;
            break;
        }
    }

    // Checking
    if(selIndex == -1)
    {
        #ifdef DEBUG
        printf("Unexpected File Format!\n");
        #endif // DEBUG

        return -1;
    }

    // Set Output Attribute Index
    keelData->outputAttrIndex = selIndex;

    // Set Outputs
    if(keelData->attrList[selIndex].attrType == NULL)
    {
        keelData->outputs = keelData->attrList[selIndex].memberCount;
    }
    else
    {
        keelData->outputs = 1;
    }

    #ifdef DEBUG
    printf("\n");
    #endif // DEBUG

    return 0;
}
