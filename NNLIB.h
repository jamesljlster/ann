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

struct TRAIN_DATA
{
    int inputs;
    int outputs;
    
    int dataAmount;
    int cols;
    
    double** trainingData;
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
    
    struct NN_LAYER* nLayerHandle;
};

int NNLIB_Config(struct NN_STRUCT* nStructPtr, double learningRate, int inputNodeCount, int outputNodeCount, int hiddenLayerCount, ...);
int NNLIB_Create(struct NN_STRUCT* nStructPtr);
int NNLIB_Delete(struct NN_STRUCT* nStructPtr);
int NNLIB_Export(struct NN_STRUCT* nStructPtr, const char* filePath);
int NNLIB_Import(struct NN_STRUCT* nStructPtr, const char* filePath);

int NNLIB_ReadTrainingData(struct TRAIN_DATA* trainDataPtr, const char* dataPath);
int NNLIB_DeleteTrainingData(struct TRAIN_DATA* trainDataPtr);

int NNLIB_RandWeight(struct NN_STRUCT* nStructPtr);
int NNLIB_SetActiveFunc(struct NN_STRUCT* nStructPtr, int assignAction, double (*activeFunc)(double), ...);
int NNLIB_SetdActiveFunc(struct NN_STRUCT* nStructPtr, int assignAction, double (*dActiveFunc)(double), ...);

int NNLIB_ForwardComputation(struct NN_STRUCT* nStructPtr, double* input, double* outputStore);

int NNLIB_SLearning_Gradient(struct NN_STRUCT* nStructPtr, double* input, double* desireOutput, double* fwCompOut, double* fwCompErr);
int NNLIB_BackPropagation_Gradient(struct NN_STRUCT* nStructPtr, double learningRate, double* dError);

//int NNLIB_SLearning(struct NN_STRUCT* nStructPtr, double* input, double* desireOutput);

int NNLIB_GetOutput(struct NN_STRUCT* nStructPtr, double* outputStore);
int NNLIB_CalcError(struct NN_STRUCT* nStructPtr, double* errList, double* desireOutput);

int NNLIB_readConing (struct NN_STRUCT* nStructPtr, char* NNConfig);
double NNTraining (double* nodeData, double* weight, int dataCount);

#endif // NNLIB_H_INCLUDED
