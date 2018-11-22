#include <stdio.h>

#include <ann.h>
#include <ann_file_proc.h>

int main(int argc, char* argv[])
{
    int i;
    int iResult;

    char** strList = NULL;
    int strCount = 0;

    char* str = "Total output= 3";

    iResult = ann_str_extract(&strList, &strCount, str, '=');
    if (iResult != ANN_NO_ERROR)
    {
        printf("ann_str_extract() failed with error: %d\n", iResult);
        return -1;
    }

    for (i = 0; i < strCount; i++)
    {
        printf("Str %d: %s\n", i, strList[i]);
    }

    return 0;
}
