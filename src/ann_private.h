#ifndef __ANN_PRIVATE_H__
#define __ANN_PRIVATE_H__

struct ANN_NODE
{
	double* weight;

	double threshold;
	double sCalc;
	double output;
};

struct ANN_LAYER
{
    double (*activeFunc)(double);
    double (*dActiveFunc)(double);

    struct ANN_NODE* nodeList;
    int nodeCount;
};

struct ANN_STRUCT
{
    int layerCount;
    struct ANN_LAYER* layerList;
};

struct ANN_CONFIG_STRUCT
{
	int inputs;
	int outputs;
	int layers;	
	int aFuncIndex;
	int* nodeList;
};

#ifdef __cplusplus
extern "C" {
#endif

void ann_delete_node(struct ANN_NODE* nodePtr);
void ann_delete_layer(struct ANN_LAYER* layerPtr);
void ann_delete_struct(struct ANN_STRUCT* structPtr);

#ifdef __cplusplus
}
#endif

#endif
