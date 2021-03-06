#include <stdlib.h>

#include "ann.h"
#include "ann_file_header.h"
#include "ann_parse.h"
#include "ann_private.h"

#include "debug.h"

int ann_import_struct(ann_t* annPtr, const char* filePath, int type);

int ann_import(ann_t* annPtr, const char* filePath)
{
    return ann_import_struct(annPtr, filePath, ANN_NETWORK_ANN);
}

int rnn_import(ann_t* annPtr, const char* filePath)
{
    return ann_import_struct(annPtr, filePath, ANN_NETWORK_RNN);
}

int ann_import_struct(ann_t* annPtr, const char* filePath, int type)
{
    int iResult;
    int retValue = ANN_NO_ERROR;

    struct ANN_STRUCT* annRef = NULL;
    struct ANN_CONFIG_STRUCT* cfgRef = NULL;
    struct ANN_FILE_STRUCT fStruct;

    LOG("enter");

    // Zero memory
    ann_fstruct_zeromem(&fStruct);

    // Create file struct
    iResult = ann_fstruct_create(&fStruct, filePath);
    if (iResult != ANN_NO_ERROR)
    {
        LOG("ann_fstruct_create() failed");
        retValue = iResult;
        goto RET;
    }

    // Memory allocation
    annRef = malloc(sizeof(struct ANN_STRUCT));
    if (annRef == NULL)
    {
        LOG("malloc() failed");
        retValue = ANN_MEM_FAILED;
        goto RET;
    }
    else
    {
        ann_zeromem(annRef);
        cfgRef = &annRef->config;
    }

    // Parse config
    iResult = ann_parse_config(cfgRef, &fStruct);
    if (iResult != ANN_NO_ERROR)
    {
        LOG("ann_parse_config() failed");
        retValue = iResult;
        goto ERR;
    }

    // Parse network
    iResult = ann_parse_network(annRef, &fStruct, type);
    if (iResult != ANN_NO_ERROR)
    {
        LOG("ann_parse_network() failed");
        retValue = iResult;
        goto ERR;
    }

    // Set default max timestep
    iResult = rnn_bptt_set_max_timestep(annRef, DEFAULT_MAX_TIMESTEP);
    if (iResult != ANN_NO_ERROR)
    {
        retValue = iResult;
        goto ERR;
    }

    // Assign value
    *annPtr = annRef;

    goto RET;

ERR:
    if (annRef != NULL) ann_delete((ann_t)annRef);

RET:
    ann_fstruct_delete(&fStruct);

    LOG("exit");

    return retValue;
}

int ann_config_import(ann_config_t* configPtr, const char* filePath)
{
    int iResult;
    int retValue = ANN_NO_ERROR;

    struct ANN_FILE_STRUCT fStruct;
    struct ANN_CONFIG_STRUCT* cfgRef = NULL;

    LOG("enter");

    // Zero memory
    ann_fstruct_zeromem(&fStruct);

    // Create file struct
    iResult = ann_fstruct_create(&fStruct, filePath);
    if (iResult != ANN_NO_ERROR)
    {
        retValue = iResult;
        goto ERR;
    }

    // Memory allocation
    cfgRef = malloc(sizeof(struct ANN_CONFIG_STRUCT));
    if (cfgRef == NULL)
    {
        retValue = ANN_NO_ERROR;
        goto RET;
    }
    else
    {
        ann_config_zeromem(cfgRef);
    }

    // Parsing
    iResult = ann_parse_config(cfgRef, &fStruct);
    if (iResult != ANN_NO_ERROR)
    {
        retValue = iResult;
        goto ERR;
    }

    // Assign value
    *configPtr = cfgRef;

    goto RET;

ERR:
    if (cfgRef != NULL) free(cfgRef);

RET:
    ann_fstruct_delete(&fStruct);
    LOG("exit");
    return retValue;
}
