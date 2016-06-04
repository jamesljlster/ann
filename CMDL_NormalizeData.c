#include <stdio.h>
#include <stdlib.h>

#include "CMDL.h"

enum CMD_NORMDATA_SETTING
{
    CMD_NORMDATA_INPUT,
    CMD_NORMDATA_OUTPUT,
    CMD_NORMDATA_ALL,
    
    CMD_NORMDATA_RESERVED
};

int CMD_NormalizeData(CMD_FUNC_ARGLIST)
{
    int i;
    int startNormIndex, endNormIndex;
    int bufProcIndex = 0;
    int normSetting = -1;
    
    char inputBuf[CMD_BUFFER_LEN] = {0};
    
    char *normSetStr[CMD_NORMDATA_RESERVED] = 
    {
        "Input",
        "Output",
        "All"
    };
    
    // Checking
    if(*traStatePtr != 1)
    {
        printf("No training dataset read!\n");
        return -1;
    }
    
    // Find Dollar Sign
    bufProcIndex = CMD_FindChar(comBuf, bufProcIndex, CMD_SET_SIGN, CMD_BUFFER_LEN);
    
    if(bufProcIndex > 0)
    {
        for(i = 0; i < CMD_NORMDATA_RESERVED; i++)
        {
            if(CMD_StrcmpUpper(normSetStr[i], &comBuf[bufProcIndex + 1]) == 0)
            {
                normSetting = i;
                break;
            }
        }
    }
    
    if(normSetting < 0)
    {
        printf("\n");
        printf("Normalize Setting:\n");
        printf("\n");
        for(i = 0; i < CMD_NORMDATA_RESERVED; i++)
        {
            printf("%s\n", normSetStr[i]);
        }
        printf("\n");
        
        while(normSetting < 0)
        {
            printf("Choose Setting: ");
            scanf(" %511s", inputBuf);
            
            for(i = 0; i < CMD_NORMDATA_RESERVED; i++)
            {
                if(CMD_StrcmpUpper(normSetStr[i], inputBuf) == 0)
                {
                    normSetting = i;
                    break;
                }
            }
        }
    }
    
    // Normalizing
    switch(normSetting)
    {
    case CMD_NORMDATA_INPUT:
        startNormIndex = 0;
        endNormIndex = KEEL_GetInputs(*traDataPtr);
        break;
        
    case CMD_NORMDATA_OUTPUT:
        startNormIndex = KEEL_GetInputs(*traDataPtr);
        endNormIndex = KEEL_GetInputs(*traDataPtr) + KEEL_GetOutputs(*traDataPtr);
        break;
        
    case CMD_NORMDATA_ALL:
        startNormIndex = 0;
        endNormIndex = KEEL_GetInputs(*traDataPtr) + KEEL_GetOutputs(*traDataPtr);
        break;
        
    default:
        return -1;
    }
    
    for(i = startNormIndex; i < KEEL_GetInputs(*traDataPtr); i++)
    {
        KEEL_Normalize(*traDataPtr, i, -1.0, 1.0);
    }
    
    for(i = KEEL_GetInputs(*traDataPtr); i < endNormIndex; i++)
    {
        KEEL_Normalize(*traDataPtr, i, 0.0, 1.0);
    }
    
    return 0;
}