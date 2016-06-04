#ifndef CMDL_H_INCLUDED
#define CMDL_H_INCLUDED

#define CMD_BUFFER_LEN  512

#define USING_KEEL_AUTOREAD

#define CMD_EXIT_STR            "Exit"
#define CMD_READ_DATASET_STR    "ReadDataSet"
#define CMD_CREATE_NN_STR       "CreateNN"
#define CMD_IMPORT_STR          "Import"
#define CMD_EXPORT_STR          "Export"
#define CMD_S_LEARNING_STR      "SLearning"
#define CMD_PREDICTION_STR      "Prediction"
#define CMD_MANUAL_TEST_STR     "ManualTest"
#define CMD_GET_OUTPUT_STR      "GetOutput"
#define CMD_FIND_ERR_STR        "FindError"
#define CMD_SET_ACTIVEFUNC_STR  "SetActiveFunc"
#define CMD_SHOW_CMDL_STR       "?"

enum CMD_ACTION
{
    CMD_READ_DATASET,
    CMD_CREATE_NN,
    CMD_IMPORT,
    CMD_EXPORT,
    CMD_S_LEARNING,
    CMD_PREDICTION,
    CMD_MANUAL_TEST,
    CMD_GET_OUTPUT,
    CMD_FIND_ERR,
    CMD_SET_ACTIVEFUNC,
    CMD_EXIT,
    CMD_SHOW_CMDL,
    
    CMD_UNKNOWN
};

#include "NNLIB.h"
#include "KEEL_DataProc.h"

#define CMD_FUNC_ARGLIST    struct NN_STRUCT* nStructPtr,                   \
                            KEEL_DATA* traDataPtr,                          \
                            char* comBuf,                                   \
                            int* nnStatePtr,                                \
                            int* traStatePtr,                               \
                            const char* cmdStr[]

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern int CMD_ReadDataSet(CMD_FUNC_ARGLIST);
extern int CMD_CreateNN(CMD_FUNC_ARGLIST);
extern int CMD_Import(CMD_FUNC_ARGLIST);
extern int CMD_Export(CMD_FUNC_ARGLIST);
extern int CMD_SLearning(CMD_FUNC_ARGLIST);
extern int CMD_Prediction(CMD_FUNC_ARGLIST);
extern int CMD_ManualTest(CMD_FUNC_ARGLIST);
extern int CMD_GetOutput(CMD_FUNC_ARGLIST);
extern int CMD_FindError(CMD_FUNC_ARGLIST);
extern int CMD_ShowCMDL(CMD_FUNC_ARGLIST);
extern int CMD_SetActiveFunc(CMD_FUNC_ARGLIST);

extern int CMD_SelectCase(const char* inputBuf, const char* cmdStr[]);
extern int CMD_GetFilePath(char* pathBuf, const char* comBuf, const char* inputMsg);
extern int CMD_FindDash(char* buffer, int startIndex, int lenLimit);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif