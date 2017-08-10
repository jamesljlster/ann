#ifndef __ANN_PRINT_H__
#define __ANN_PRINT_H__

#include <stdio.h>
#include "ann_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void ann_fprint_header(FILE* fptr, int type);
void ann_fprint_config(FILE* fptr, struct ANN_CONFIG_STRUCT* cfgPtr);
void ann_fprint_threshold(FILE* fptr, struct ANN_STRUCT* asPtr);
void ann_fprint_weight(FILE* fptr, struct ANN_STRUCT* asPtr);
void ann_fprint_recurrent_weight(FILE* fptr, struct ANN_STRUCT* asPtr);

#ifdef __cplusplus
}
#endif

#endif
