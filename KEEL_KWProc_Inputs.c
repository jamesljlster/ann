#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "KEEL_DataProc.h"
#include "KEEL_PrivateFunc.h"

//#define DEBUG

int KEEL_KWProc_Inputs(KEEL_DATA keelData, char* fileBuffer, const char* keyword)
{
    int i, iResult;
    int selIndex;
    int procIndex;

    int* tmpIndexLPtr;  // Temp Index List Pointer

    char procBuffer[KEEL_BUFFER_LEN] = {0};
    char scanFormat[KEEL_BUFFER_LEN] = {0};
    char tempBuffer[KEEL_BUFFER_LEN] = {0};

    // Find Input List
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

    // Find All Input Attribute Index
    procIndex = 0;
    while(1)
    {
        // Get String on List
        sprintf(scanFormat, " %%[^,]s ");
        sscanf(&procBuffer[procIndex], scanFormat, tempBuffer);

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

        // Memory Allocation: Input Attribute Index List
        keelData->inputs++;
        tmpIndexLPtr = (int*)realloc(keelData->inputAttrIndexList, keelData->inputs * sizeof(int));
        if(tmpIndexLPtr == NULL)
        {
            #ifdef DEBUG
            printf("Memory Allocation Failed!\n");
            #endif // DEBUG

            keelData->inputs--;
            return -1;
        }
        else
        {
            keelData->inputAttrIndexList = tmpIndexLPtr;
        }

        // Insert Attribute Index to Index List
        keelData->inputAttrIndexList[keelData->inputs - 1] = selIndex;

        // Find Next
        procIndex = KEEL_FindChar(procBuffer, procIndex, ',', KEEL_BUFFER_LEN);
        if(procIndex == -1)
        {
            break;
        }
        else
        {
            procIndex++;
        }
    }

    #ifdef DEBUG
    printf("\n");
    #endif // DEBUG

    return 0;
}
