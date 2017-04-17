#ifndef __ANN_PRIVATE_H__
#define __ANN_PRIVATE_H__

#include "ann_types.h"

#ifdef __cplusplus
extern "C" {
#endif

int ann_clone_config_struct(struct ANN_CONFIG_STRUCT* dst, struct ANN_CONFIG_STRUCT* src);

int ann_allocate_network(struct ANN_STRUCT* sptr);

void ann_zeromem(struct ANN_STRUCT* asPtr);
void ann_config_zeromem(struct ANN_CONFIG_STRUCT* cfgPtr);

void ann_config_delete_struct(struct ANN_CONFIG_STRUCT* cfgPtr);

void ann_delete_node(struct ANN_NODE* nodePtr);
void ann_delete_layer(struct ANN_LAYER* layerPtr);
void ann_delete_struct(struct ANN_STRUCT* structPtr);

int ann_set_weight_struct(struct ANN_STRUCT* sptr, int layerIndex, int preNodeIndex, int nodeIndex, double value);
int ann_set_threshold_struct(struct ANN_STRUCT* sptr, int layerIndex, int nodeIndex, double value);

double ann_rand();

#ifdef __cplusplus
}
#endif

#endif
