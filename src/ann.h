#ifndef __ANN_H__
#define __ANN_H__

enum ANN_RETUEN_VALUE
{
	ANN_NO_ERROR		= 0,
	ANN_MEM_FAILED		= -1,
	ANN_FILE_FAILED		= -2,
	ANN_SYNTAX_ERROR	= -3
};

typedef void* ann_t;
typedef void* ann_config_t;

#ifdef __cplusplus
extern "C" {
#endif

int ann_create(ann_t* annPtr, int inputs, int outputs, int hiddenLayers, ...);
int ann_create_by_config(ann_t* annPtr, ann_config_t config);
int ann_import(ann_t* annPtr, const char* filePath);
int ann_export(ann_t ann, const char* filePath);
int ann_delete(ann_t ann);

int ann_config_create(ann_config_t* configPtr, int inputs, int outputs);
int ann_config_import(ann_config_t* configPtr, const char* filePath);
int ann_config_export(ann_config_t config, const char* filePath);
int ann_config_delete(ann_config_t config);
int ann_config_add_hidden_layer(ann_config_t config, int nodes);
void ann_config_print(ann_config_t config);

int ann_forward_computation(ann_t ann);

#ifdef __cplusplus
}
#endif

#endif
