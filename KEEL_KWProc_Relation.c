#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "KEEL_DataProc.h"
#include "KEEL_PrivateFunc.h"

//#define DEBUG

int KEEL_KWProc_Relation(KEEL_DATA keelData, char* fileBuffer, const char* keyword)
{
    char scanFormat[KEEL_BUFFER_LEN] = {0};
    char procBuffer[KEEL_BUFFER_LEN] = {0};

    sprintf(scanFormat, "%s %%s", keyword);
    sscanf(fileBuffer, scanFormat, procBuffer);

    #ifdef DEBUG
    printf("Processed Buffer: %s\n", procBuffer);
    #endif // DEBUG

    keelData->name = (char*)calloc(strlen(procBuffer) + 1, sizeof(char));
    if(keelData->name == NULL)
    {
        #ifdef DEBUG
        printf("Memory Allocation Failed!\n");
        #endif // DEBUG

        return -1;
    }
    else
    {
        strcpy(keelData->name, procBuffer);
    }

    return 0;
}
