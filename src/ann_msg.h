#ifndef __ANN_MSG_H__
#define __ANN_MSG_H__

enum ANN_RETURN_VALUE_MSG
{
    ANN_NO_ERROR_MSG,        //
    ANN_MEM_FAILED_MSG,      //
    ANN_FILE_FAILED_MSG,     //
    ANN_SYNTAX_ERROR_MSG,    //
    ANN_INFO_NOT_FOUND_MSG,  //
    ANN_OUT_OF_RANGE_MSG,    //
    ANN_INVALID_ARG_MSG,     //

    ANN_NOT_RETVALUE_MSG  //
};

extern char* ann_error_msg[];

#endif
