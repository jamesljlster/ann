#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "KEEL_DataProc.h"
#include "KEEL_PrivateFunc.h"

#define KEEL_KEYWORD_RELATION_STR   "@relation"
#define KEEL_KEYWORD_ATTRIBUTE_STR  "@attribute"
#define KEEL_KEYWORD_INPUTS_STR     "@inputs"
#define KEEL_KEYWORD_OUTPUTS_STR    "@outputs"
#define KEEL_KEYWORD_DATA_STR       "@data"

#define KEEL_KWPROC_ARGLIST KEEL_DATA keelData, char* fileBuffer, const char* keyword

enum KEEL_KEYWORD
{
    KEEL_KEYWORD_RELATION,
    KEEL_KEYWORD_ATTRIBUTE,
    KEEL_KEYWORD_INPUTS,
    KEEL_KEYWORD_OUTPUTS,
    KEEL_KEYWORD_DATA,

    KEEL_KEYWORD_RESERVE
};

//#define DEBUG

KEEL_DATA KEEL_ReadDataset(const char* dataPath)
{
    int i, j;
    int iResult;
    int kwDetect;   // Keyword Detection

    double* dataTmp = NULL;

    KEEL_DATA keelData = NULL;
    FILE* fileRead;

    char fileBuffer[KEEL_BUFFER_LEN] = {0};
    char procBuffer[KEEL_BUFFER_LEN] = {0};

    const char* keelKeyword[KEEL_KEYWORD_RESERVE];
    int (*KEEL_KWProc_Func[KEEL_KEYWORD_RESERVE])(KEEL_DATA keelData, char* fileBuffer, const char* keyword);

    keelKeyword[KEEL_KEYWORD_RELATION]  = KEEL_KEYWORD_RELATION_STR;
    keelKeyword[KEEL_KEYWORD_ATTRIBUTE] = KEEL_KEYWORD_ATTRIBUTE_STR;
    keelKeyword[KEEL_KEYWORD_INPUTS]    = KEEL_KEYWORD_INPUTS_STR;
    keelKeyword[KEEL_KEYWORD_OUTPUTS]   = KEEL_KEYWORD_OUTPUTS_STR;
    keelKeyword[KEEL_KEYWORD_DATA]      = KEEL_KEYWORD_DATA_STR;

    KEEL_KWProc_Func[KEEL_KEYWORD_RELATION]     = KEEL_KWProc_Relation;
    KEEL_KWProc_Func[KEEL_KEYWORD_ATTRIBUTE]    = KEEL_KWProc_Attribute;
    KEEL_KWProc_Func[KEEL_KEYWORD_INPUTS]       = KEEL_KWProc_Inputs;
    KEEL_KWProc_Func[KEEL_KEYWORD_OUTPUTS]      = KEEL_KWProc_Outputs;

    // Memory Allocation: KEEL_DATA
    keelData = (KEEL_DATA)malloc(sizeof(struct _KEEL_DATA));
    if(keelData == NULL)
    {
        #ifdef DEBUG
        printf("Memory Allocation Failed!\n");
        #endif // DEBUG

        return NULL;
    }
    else
    {
        memset(keelData, 0, sizeof(struct _KEEL_DATA));
    }

    // Open Dataset
    fileRead = fopen(dataPath, "r");
    if(fileRead == NULL)
    {
        #ifdef DEBUG
        printf("Failed to open %s\n", dataPath);
        #endif // DEBUG

        return NULL;
    }

    // Read KEEL Header
    while(1)
    {
        fscanf(fileRead, " %512[^\n]s\n", fileBuffer);

        #ifdef DEBUG
        printf("Scanned String: %s\n", fileBuffer);
        #endif // DEBUG

        kwDetect = -1;
        for(i = 0; i < KEEL_KEYWORD_RESERVE; i++)
        {
            iResult = strncmp(keelKeyword[i], fileBuffer, strlen(keelKeyword[i]));
            if(iResult == 0)
            {
                kwDetect = i;
                break;
            }
        }

        #ifdef DEBUG
        printf("Keyword Detect: %d\n", kwDetect);
        printf("\n");
        #endif // DEBUG

        // Scan Content
        if(kwDetect == KEEL_KEYWORD_DATA)
        {
            break;
        }
        else
        {
            iResult = KEEL_KWProc_Func[kwDetect](keelData, fileBuffer, keelKeyword[kwDetect]);
            if(iResult != 0)
            {
                return NULL;
            }
        }
    }

    // Checking Inputs and Outputs
    if(keelData->outputs == 0)
    {
        if(keelData->attrList[keelData->attrAmount - 1].attrType == NULL)
        {
            keelData->outputs = keelData->attrList[keelData->attrAmount - 1].memberCount;
        }
        else
        {
            keelData->outputs = 1;
        }
    }

    if(keelData->inputs == 0)
    {
        keelData->inputs = keelData->attrAmount - 1;
    }

    // Read KEEL Content
    keelData->dataCols = keelData->inputs + keelData->outputs;
    while(!feof(fileRead))
    {
        keelData->dataRows++;
        dataTmp = realloc(keelData->data, keelData->dataRows * keelData->dataCols * sizeof(double));
        if(dataTmp == NULL)
        {
            #ifdef DEBUG
            printf("Memory Allocation Failed!\n");
            #endif // DEBUG

            free(keelData->data);
            fclose(fileRead);
        }
        else
        {
            keelData->data = dataTmp;
        }

        // Scan Inputs
        i = 0;
        for(j = 0; j < keelData->inputs; j++, i++)
        {
            fscanf(fileRead, "%lf, ", &(keelData->data[(keelData->dataRows - 1) * keelData->dataCols + i]));
        }

        // Scan Outputs
        fscanf(fileRead, " %s\n", procBuffer);

        if(keelData->attrList[keelData->outputAttrIndex].attrType == NULL)
        {
            for(j = 0; j < keelData->outputs; j++, i++)
            {
                iResult = strncmp(keelData->attrList[keelData->outputAttrIndex].member[j], procBuffer, strlen(keelData->attrList[keelData->outputAttrIndex].member[j]));
                if(iResult == 0)
                {
                    keelData->data[(keelData->dataRows - 1) * keelData->dataCols + i] = 1;
                }
                else
                {
                    keelData->data[(keelData->dataRows - 1) * keelData->dataCols + i] = 0;
                }
            }
        }
        else
        {
            keelData->data[(keelData->dataRows - 1) * keelData->dataCols + i] = atof(procBuffer);
        }
    }

    fclose(fileRead);

    return keelData;
}
