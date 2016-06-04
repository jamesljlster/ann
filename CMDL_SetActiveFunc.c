#include <stdio.h>
#include <stdlib.h>

#include "NNLIB.h"
#include "CMDL.h"
#include "ActiveFunc.h"

int CMD_SetActiveFunc(CMD_FUNC_ARGLIST)
{
    int i;
    int tmpConvert;
    int bufProcIndex;
    
    // Checking
    if(*nnStatePtr != 1)
    {
        printf("No neural networks created!\n");
        return -1;
    }
    
    // Print Activation Function List
    printf("\n");
    printf("Activation Function List:\n\n");
    for(i = 0; i < AFUNC_RESERVED; i++)
    {
        printf("%d\t: %s\n", i + 1, aFuncMsg[i]);
    }
    printf("\n");
    
    // Get Activation Function List
    bufProcIndex = 0;
    for(i = 0; i < nStructPtr->layerCount - 1; i++)
    {
        tmpConvert = 0;
        bufProcIndex = CMD_FindDash(comBuf, bufProcIndex, CMD_BUFFER_LEN);
        if(bufProcIndex > 0)
        {
            bufProcIndex++;
            if(comBuf[bufProcIndex] != '\0')
            {
                tmpConvert = atoi(&comBuf[bufProcIndex]);
            }
        }
        
        if(tmpConvert > 0)
        {
            nStructPtr->aFuncIndexList[i] = tmpConvert - 1;
        }
        else
        {
            printf("Assign Layer %d Activation Function: ", i + 1);
            scanf(" %d", &nStructPtr->aFuncIndexList[i]);
        }
    }
    
    // Set Activation Function
    NNLIB_SetActiveFunc_Index(nStructPtr, nStructPtr->aFuncIndexList);
    NNLIB_SetdActiveFunc_Index(nStructPtr, nStructPtr->aFuncIndexList);
    
    return 0;
}
