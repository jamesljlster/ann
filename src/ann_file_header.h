#ifndef __ANN_FILE_HEADER_H__
#define __ANN_FILE_HEADER_H__

enum ANN_FILE_HEADER_LIST
{
    ANN_HEADER_APPLICATION,       //
    ANN_HEADER_TOPOLOGY,          //
    ANN_HEADER_TFUNC,             //
    ANN_HEADER_TRAINING_INFO,     //
    ANN_HEADER_TOTAL_NODE,        //
    ANN_HEADER_THRESHOLD_VALUE,   //
    ANN_HEADER_WEIGHT_FACTOR,     //
    ANN_HEADER_RECURRENT_WEIGHT,  //

    ANN_HEADER_HEADER_LIST_COUNT  //
};

enum ANN_HEADER_APPLICATION_LIST
{
    ANN_HEADER_APPLICATION_ANN_MSG,  //
    ANN_HEADER_APPLICATION_RNN_MSG   //
};

enum ANN_HEADER_TOPOLOGY_LIST
{
    ANN_HEADER_TOPOLOGY_INPUTS,         //
    ANN_HEADER_TOPOLOGY_OUTPUTS,        //
    ANN_HEADER_TOPOLOGY_LAYERS,         //
    ANN_HEADER_TOPOLOGY_TRANSFER_FUNC,  //

    ANN_HEADER_TOPOLOGY_LIST_COUNT  //
};

enum ANN_HEADER_TFUNC_LIST
{
    ANN_HEADER_TFUNC_MSG  //
};

enum ANN_HEADER_TRAINING_INFO_LIST
{
    ANN_HEADER_TRAINING_INFO_LEARNING_RATE,  //
    ANN_HEADER_TRAINING_INFO_MOMENTUM_COEF,  //

    ANN_HEADER_TRAINING_INFO_LIST_COUNT  //
};

enum ANN_HEADER_TOTAL_NODE_LIST
{
    ANN_HEADER_TOTAL_NODE_MSG  //
};

enum ANN_HEADER_THREDHOLD_VALUE_LIST
{
    ANN_HEADER_THRESHOLD_VALUE_MSG  //
};

enum ANN_HEADER_WEIGHT_LIST
{
    ANN_HEADER_WEIGHT_MSG  //
};

enum ANN_HEADER_RECURRENT_LIST
{
    ANN_HEADER_RECURRENT_MSG  //
};

extern char* ann_file_header[];
extern char* ann_header_application[];
extern char* ann_header_topology[];
extern char* ann_header_tfunc[];
extern char* ann_header_training_info[];
extern char* ann_header_total_node[];
extern char* ann_header_threshold_value[];
extern char* ann_header_weight_factor[];
extern char* ann_header_recurrent_weight[];

#ifdef __cplusplus
extern "C"
{
#endif

    int ann_get_topology_content_id(char* src);
    int ann_get_training_content_id(char* src);

#ifdef __cplusplus
}
#endif

#endif
