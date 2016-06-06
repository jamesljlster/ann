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
        bufProcIndex = CMD_FindChar(comBuf, bufProcIndex, CMD_NUM_SIGN, CMD_BUFFER_LEN);
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
            printf("Assign Layer %d - %d Activation Function: %d\n", i + 1, nStructPtr->layerCount - 1, tmpConvert);
            nStructPtr->aFuncIndexList[i] = tmpConvert - 1;
        }
        else
        {
            tmpConvert = 0;
            while(tmpConvert == 0 || tmpConvert > AFUNC_RESERVED)
            {
                printf("Assign Layer %d - %d Activation Function: ", i + 1, nStructPtr->layerCount - 1);
                scanf(" %d", &tmpConvert);
            }
            
            nStructPtr->aFuncIndexList[i] = tmpConvert - 1;
        }
    }
    
    // Set Activation Function
    NNLIB_SetActiveFunc_Index(nStructPtr, nStructPtr->aFuncIndexList);
    NNLIB_SetdActiveFunc_Index(nStructPtr, nStructPtr->aFuncIndexList);
    
    return 0;
}
