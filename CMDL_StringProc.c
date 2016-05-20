#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "NNLIB.h"
#include "CMDL.h"

int CMD_SelectCase(const char* inputBuf, const char* cmdStr[])
{
    int i, j;
    int caseSelected = CMD_UNKNOWN;
    
    char procBuffer[CMD_BUFFER_LEN] = {0};
    char comBuf[CMD_BUFFER_LEN] = {0};
    
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

int CMD_GetFilePath(char* pathBuf, const char* comBuf, const char* inputMsg)
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

int CMD_FindDash(char* buffer, int startIndex, int lenLimit)
{
    int i;
    
    if(startIndex >= 0)
    {
        i = startIndex;
    }
    else
    {
        return -1;
    }
    
    while(buffer[i] != '-')
    {
        if(buffer[i] == '\0')
        {
            return -1;
        }
        else
        {
            i++;
        }
        
        if(i >= lenLimit)
        {
            return -1;
        }
    }
    
    return i;
}
