#include <stdlib.h>
#include <string.h>

#include "NNLIB.h"
#include "Alloc2DArray.h"

int NNLIB_Prediction_Hard(struct NN_STRUCT* nStructPtr, double* prediction, double* desireOutput)
{
    int i, iResult;
    
    char* tarConvert;
    char* outConvert;
    
    // Memory Allocation
    tarConvert = (char*)calloc(nStructPtr->outputNodeCount + 1, sizeof(char));
    if(tarConvert == NULL)
    {
        return -1;
    }
    
    outConvert = (char*)calloc(nStructPtr->outputNodeCount + 1, sizeof(char));
    if(outConvert == NULL)
    {
        free(tarConvert);
        return -1;
    }
    
    for(i = 0; i < nStructPtr->outputNodeCount; i++)
    {
        if(desireOutput[i] > 0.75)
        {
            tarConvert[i] = '1';
        }
        else if(desireOutput[i] < 0.25)
        {
            tarConvert[i] = '0';
        }
        else
        {
            free(tarConvert);
            free(outConvert);
            return 0;
        }
        
        if(prediction[i] > 0.75)
        {
            outConvert[i] = '1';
        }
        else if(prediction[i] < 0.25)
        {
            outConvert[i] = '0';
        }
        else
        {
            free(tarConvert);
            free(outConvert);
            return 0;
        }
    }
    
    iResult = (strncmp(tarConvert, outConvert, nStructPtr->outputNodeCount) == 0) ? 1 : 0;
    
    // Cleanup
    free(tarConvert);
    free(outConvert);
    
    return iResult;
}
