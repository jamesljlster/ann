#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "KEEL_DataProc.h"
#include "KEEL_PrivateFunc.h"

//#define DEBUG

int KEEL_KWProc_Attribute(KEEL_DATA keelData, char* fileBuffer, const char* keyword)
{
    int procIndex;
    int loopCounter;

    char procBuffer[KEEL_BUFFER_LEN] = {0};
    char tempBuffer[KEEL_BUFFER_LEN] = {0};
    char scanFormat[KEEL_BUFFER_LEN] = {0};

    char** tmpStrLPtr = NULL;   // Temp string list pointer

    struct KEEL_ATTRIBUTE* attrTmpPtr = NULL;

    keelData->attrAmount++;
    attrTmpPtr = (struct KEEL_ATTRIBUTE*)realloc(keelData->attrList, keelData->attrAmount* sizeof(struct KEEL_ATTRIBUTE));
    if(attrTmpPtr == NULL)
    {
        #ifdef DEBUG
        printf("Memory Allocation Failed!\n");
        #endif // DEBUG

        keelData->attrAmount--;
        return -1;
    }
    else
    {
        keelData->attrList = attrTmpPtr;
        memset((void*)&(keelData->attrList[keelData->attrAmount - 1]), 0, sizeof(struct KEEL_ATTRIBUTE));
    }

    // Process Attribute Name and Type
    procIndex = 0;
    loopCounter = 0;
    while(1)
    {
        procIndex = KEEL_FindChar(fileBuffer, procIndex, ' ', KEEL_BUFFER_LEN);
        procIndex++;

        sprintf(scanFormat, " %%s ");
        sscanf(&fileBuffer[procIndex], scanFormat, procBuffer);

        #ifdef DEBUG
        printf("Processed Buffer: %s\n", procBuffer);
        #endif // DEBUG

        if(procBuffer[0] == '{' || procBuffer[0] == '[')
        {
            break;
        }

        if(loopCounter == 0)
        {
            keelData->attrList[keelData->attrAmount - 1].attrName = (char*)calloc(strlen(procBuffer) + 1, sizeof(char));
            if(keelData->attrList[keelData->attrAmount - 1].attrName == NULL)
            {
                #ifdef DEBUG
                printf("Memory Allocation Failed!\n");
                #endif // DEBUG

                return -1;
            }
            else
            {
                strcpy(keelData->attrList[keelData->attrAmount - 1].attrName, procBuffer);

                #ifdef DEBUG
                printf("attrName = %s\n", keelData->attrList[keelData->attrAmount - 1].attrName);
                #endif // DEBUG
            }
        }
        else if(loopCounter == 1)
        {
            keelData->attrList[keelData->attrAmount - 1].attrType = (char*)calloc(strlen(procBuffer) + 1, sizeof(char));
            if(keelData->attrList[keelData->attrAmount - 1].attrType == NULL)
            {
                #ifdef DEBUG
                printf("Memory Allocation Failed!\n");
                #endif // DEBUG

                return -1;
            }
            else
            {
                strcpy(keelData->attrList[keelData->attrAmount - 1].attrType, procBuffer);

                #ifdef DEBUG
                printf("attrType = %s\n", keelData->attrList[keelData->attrAmount - 1].attrType);
                #endif // DEBUG
            }
        }
        else
        {
            #ifdef DEBUG
            printf("Process Attribute Name and Type Finished.\n");
            #endif // DEBUG

            break;
        }

        loopCounter++;
    }

    #ifdef DEBUG
    printf("\n");
    #endif // DEBUG

    // Find '{' or '['
    procIndex = KEEL_FindChar(fileBuffer, 0, '{', KEEL_BUFFER_LEN);
    if(procIndex == -1)
    {
        procIndex = KEEL_FindChar(fileBuffer, 0, '[', KEEL_BUFFER_LEN);
        if(procIndex == -1)
        {
            #ifdef DEBUG
            printf("Unexpected File Format!\n");
            #endif // DEBUG

            return -1;
        }
    }

    if(procIndex != -1)
    {
        strcpy(procBuffer, &fileBuffer[procIndex + 1]);
        procBuffer[strlen(procBuffer) - 1] = '\0';

        #ifdef DEBUG
        printf("Processed Member Buffer: %s\n", procBuffer);
        #endif // DEBUG

        // Process Member
        procIndex = 0;
        while(1)
        {
            sprintf(scanFormat, " %%[^,]s");
            sscanf(&procBuffer[procIndex], scanFormat, tempBuffer);

            #ifdef DEBUG
            printf("Processed Buffer: %s\n", tempBuffer);
            #endif // DEBUG

            // Check if string member
            if(atof(tempBuffer) == 0 && tempBuffer[0] > '9')
            {
                keelData->attrList[keelData->attrAmount - 1].stringMember = 1;
            }

            // Memory Allocation: Attribute Member List
            keelData->attrList[keelData->attrAmount - 1].memberCount++;
            tmpStrLPtr = (char**)realloc(keelData->attrList[keelData->attrAmount - 1].member, keelData->attrList[keelData->attrAmount - 1].memberCount * sizeof(char*));
            if(tmpStrLPtr == NULL)
            {
                #ifdef DEBUG
                printf("Memory Allocation Failed!\n");
                #endif // DEBUG

                keelData->attrList[keelData->attrAmount - 1].memberCount--;
                return -1;
            }
            else
            {
                keelData->attrList[keelData->attrAmount - 1].member = tmpStrLPtr;
            }

            // Memory Allocation: Attribute Member String
            keelData->attrList[keelData->attrAmount - 1].member[keelData->attrList[keelData->attrAmount - 1].memberCount - 1] = (char*)calloc(strlen(tempBuffer) + 1, sizeof(char));
            if(keelData->attrList[keelData->attrAmount - 1].member[keelData->attrList[keelData->attrAmount - 1].memberCount - 1] == NULL)
            {
                #ifdef DEBUG
                printf("Memory Allocation Failed!\n");
                #endif // DEBUG

                return -1;
            }
            else
            {
                strcpy(keelData->attrList[keelData->attrAmount - 1].member[keelData->attrList[keelData->attrAmount - 1].memberCount - 1], tempBuffer);
            }

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
        #endif
    }

    return 0;
}
