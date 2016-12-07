#include <stdarg.h>

#include "NNLIB.h"
#include "ActiveFunc.h"

int NNLIB_SetActiveFunc_Index(struct NN_STRUCT* nStructPtr, int* activeFuncList)
{
    int i;
    
    for(i = 1; i < nStructPtr->layerCount; i++)
    {
        nStructPtr->nLayerHandle[i].activeFunc = aFuncBox[activeFuncList[i - 1]];
    }
    
    return 0;
}

int NNLIB_SetdActiveFunc_Index(struct NN_STRUCT* nStructPtr, int* dActiveFuncList)
{
    int i;
    
    for(i = 1; i < nStructPtr->layerCount; i++)
    {
        nStructPtr->nLayerHandle[i].dActiveFunc = aFuncBox_Derivative[dActiveFuncList[i - 1]];
    }
    
    return 0;
}

int NNLIB_SetdActiveFunc(struct NN_STRUCT* nStructPtr, int assignAction, double (*dActiveFunc)(double), ...)
{
    int i;
    
    va_list argList;
    
    if(assignAction == NNLIB_MANUALLY_ASSIGN)
    {
        nStructPtr->nLayerHandle[1].dActiveFunc = dActiveFunc;
        
        va_start(argList, dActiveFunc);
        for(i=2; i<nStructPtr->layerCount; i++)
        {
            nStructPtr->nLayerHandle[i].dActiveFunc = va_arg(argList, double (*)(double));
        }
        va_end(argList);
    }
    else
    {
        for(i=1; i<nStructPtr->layerCount; i++)
        {
            nStructPtr->nLayerHandle[i].dActiveFunc = dActiveFunc;
        }
    }
    
    return 0;
}

int NNLIB_SetActiveFunc(struct NN_STRUCT* nStructPtr, int assignAction, double (*activeFunc)(double), ...)
{
    int i;
    
    va_list argList;
    
    if(assignAction == NNLIB_MANUALLY_ASSIGN)
    {
        nStructPtr->nLayerHandle[1].activeFunc = activeFunc;
        
        va_start(argList, activeFunc);
        for(i=2; i<nStructPtr->layerCount; i++)
        {
            nStructPtr->nLayerHandle[i].activeFunc = va_arg(argList, double (*)(double));
        }
        va_end(argList);
    }
    else
    {
        for(i=1; i<nStructPtr->layerCount; i++)
        {
            nStructPtr->nLayerHandle[i].activeFunc = activeFunc;
        }
    }
    
    return 0;
}
