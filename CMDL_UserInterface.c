#include <stdio.h>
#include <stdlib.h>

#include "NNLIB.h"
#include "CMDL.h"

int CMD_ShowCMDL(CMD_FUNC_ARGLIST)
{
    int i;
    
    printf("=== Command List ===\n");
    for(i = 0; i < CMD_UNKNOWN; i++)
    {
        printf("%s\n", cmdStr[i]);
    }
    
    return 0;
}

int CMD_ManualTest(CMD_FUNC_ARGLIST)
{
    int i;
    char kbin;
    
    double* nnInput = NULL;
    double* nnOutput = NULL;
    
    // Memory Allocation
    nnInput = (double*)calloc(nStructPtr->inputNodeCount, sizeof(double));
    if(nnInput == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return -1;
    }
    
    nnOutput = (double*)calloc(nStructPtr->outputNodeCount, sizeof(double));
    if(nnOutput == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(nnInput);
        return -1;
    }
    
    // Checking
    if(*nnStatePtr != 1)
    {
        printf("No neural networks created!\n");
        free(nnInput);
        free(nnOutput);
        return -1;
    }
    while(1)
    {
        printf("Press ESC to exit or other keys to Test the Neural Networks...");
        scanf(" %c", &kbin);
        if(kbin == 27)
        {
            printf("\n");
            break;
        }
        else
        {
            printf("\n");
        }
        
        // Input Test Data
        for(i = 0; i < nStructPtr->inputNodeCount; i++)
        {
            printf("Assign %d of %d input: ", i + 1, nStructPtr->inputNodeCount);
            scanf("%lf", &nnInput[i]);
        }
        
        NNLIB_ForwardComputation(nStructPtr, nnInput, nnOutput);
        
        printf("Neural Network Output: ");
        for(i = 0; i < nStructPtr->outputNodeCount; i++)
        {
            printf("%lf", nnOutput[i]);
            
            if(i == nStructPtr->outputNodeCount - 1)
            {
                printf("\n\n");
            }
            else
            {
                printf(", ");
            }
        }
    }
    
    // Cleanup
    free(nnInput);
    free(nnOutput);
    
    return 0;
}
