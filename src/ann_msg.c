#include <stdlib.h>

#include "ann.h"
#include "ann_msg.h"

char* ann_error_msg[] = {
    "No error",                            //
    "Memory allocation failed",            //
    "File processing failed",              //
    "Wrong file format or syntax",         //
    "Required information was not found",  //
    "Operation out of range",              //
    "Invalid argument(s) or setting(s)",   //

    "Not a return value in ann library"  //
};

const char* ann_get_error_msg(int retValue)
{
    const char* retPtr = NULL;

    if (retValue >= 0)
    {
        retPtr = ann_error_msg[ANN_NO_ERROR_MSG];
    }
    else
    {
        switch (retValue)
        {
            case ANN_MEM_FAILED:
                retPtr = ann_error_msg[ANN_MEM_FAILED_MSG];
                break;

            case ANN_FILE_FAILED:
                retPtr = ann_error_msg[ANN_FILE_FAILED_MSG];
                break;

            case ANN_SYNTAX_ERROR:
                retPtr = ann_error_msg[ANN_SYNTAX_ERROR_MSG];
                break;

            case ANN_INFO_NOT_FOUND:
                retPtr = ann_error_msg[ANN_INFO_NOT_FOUND_MSG];
                break;

            case ANN_OUT_OF_RANGE:
                retPtr = ann_error_msg[ANN_OUT_OF_RANGE_MSG];
                break;

            case ANN_INVALID_ARG:
                retPtr = ann_error_msg[ANN_INVALID_ARG_MSG];
                break;

            default:
                retPtr = ann_error_msg[ANN_NOT_RETVALUE_MSG];
        }
    }

    return retPtr;
}
