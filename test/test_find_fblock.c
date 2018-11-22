#include <stdio.h>

#include <ann.h>
#include <ann_file_header.h>
#include <ann_file_proc.h>

int main(int argc, char* argv[])
{
    int i;
    int iResult;
    struct ANN_FILE_STRUCT fStruct;
    struct ANN_FILE_BLOCK* fptr = NULL;

    // Checking
    if (argc < 2)
    {
        printf("Assing a .vgn file to run the test.\n");
        return -1;
    }

    iResult = ann_fstruct_create(&fStruct, argv[1]);
    if (iResult != ANN_NO_ERROR)
    {
        printf("ann_fstruct_create() failed with error: %d\n", iResult);
        return -1;
    }

    for (i = 0; i < 6; i++)
    {
        fptr = ann_find_fblock(&fStruct, i);
        if (fptr == NULL)
        {
            printf("Find %s file block failed!\n", ann_file_header[i]);
            return -1;
        }
        else
        {
            ann_fblock_print(fptr);
        }
    }

    ann_fstruct_delete(&fStruct);

    return 0;
}
