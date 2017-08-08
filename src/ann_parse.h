#ifndef __ANN_PARSE_H__
#define __ANN_PARSE_H__

#include "ann_types.h"
#include "ann_file_proc.h"

#ifdef __cplusplus
extern "C" {
#endif

int ann_parse_config(struct ANN_CONFIG_STRUCT* cfgPtr, struct ANN_FILE_STRUCT* fsPtr);
int ann_parse_network(struct ANN_STRUCT* asPtr, struct ANN_FILE_STRUCT* fsPtr, int type);

#ifdef __cplusplus
}
#endif

#endif
