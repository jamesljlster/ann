#ifndef NNLIB_H_INCLUDED
#define NNLIB_H_INCLUDED

enum NNLIB_NODE_TYPE
{
    INPUT_NODE,
    HIDDEN_NODE,
    OUTPUT_NODE
};

enum NNLIB_ACTFUNC_SETTING
{
    NNLIB_ASSIGN_SAME_ACTFUNC,
    NNLIB_MANUALLY_ASSIGN
};

struct NN_NODE
{
    int nodeType;

    double* weight;
    
    double threshold;
    double sCalc;
    double output;
};

struct NN_LAYER
{
    double (*activeFunc)(double);
    double (*dActiveFunc)(double);

    struct NN_NODE* nodeList;
    int nodeCount;
};

struct NN_STRUCT
{
    double learningRate;
    
    int inputNodeCount;
    int outputNodeCount;
    int layerCount;

    int* nodesEachLayer;
    int* aFuncIndexList;
    
    struct NN_LAYER* nLayerHandle;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern int NNLIB_Config(struct NN_STRUCT* nStructPtr, double learningRate, int inputNodeCount, int outputNodeCount, int hiddenLayerCount, ...);
extern int NNLIB_Create(struct NN_STRUCT* nStructPtr);
extern int NNLIB_Delete(struct NN_STRUCT* nStructPtr);
extern int NNLIB_Export(struct NN_STRUCT* nStructPtr, const char* filePath);
extern int NNLIB_Import(struct NN_STRUCT* nStructPtr, const char* filePath);

extern int NNLIB_RandWeight(struct NN_STRUCT* nStructPtr);

extern int NNLIB_SetActiveFunc(struct NN_STRUCT* nStructPtr, int assignAction, double (*activeFunc)(double), ...);
extern int NNLIB_SetdActiveFunc(struct NN_STRUCT* nStructPtr, int assignAction, double (*dActiveFunc)(double), ...);

extern int NNLIB_SetActiveFunc_Index(struct NN_STRUCT* nStructPtr, int* activeFuncList);
extern int NNLIB_SetdActiveFunc_Index(struct NN_STRUCT* nStructPtr, int* dActiveFuncList);

extern int NNLIB_ForwardComputation(struct NN_STRUCT* nStructPtr, double* input, double* outputStore);

extern int NNLIB_SLearning_Gradient(struct NN_STRUCT* nStructPtr, double* input, double* desireOutput, double* fwCompOut, double* fwCompErr);
extern int NNLIB_BackPropagation_Gradient(struct NN_STRUCT* nStructPtr, double learningRate, double* dError);

extern int NNLIB_Prediction_Hard(struct NN_STRUCT* nStructPtr, double* prediction, double* desireOutput);
extern int NNLIB_Prediction_Soft(struct NN_STRUCT* nStructPtr, double* prediction, double* desireOutput);

extern int NNLIB_GetOutput(struct NN_STRUCT* nStructPtr, double* outputStore);
extern int NNLIB_CalcError(struct NN_STRUCT* nStructPtr, double* errList, double* desireOutput);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // NNLIB_H_INCLUDED
