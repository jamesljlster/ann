#include <stdio.h>

#include <ann.h>
#include <ann_file_proc.h>

int main(int argc, char* argv[])
{
    int iResult;
    struct ANN_FILE_STRUCT fStruct;

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

    ann_fstruct_print(&fStruct);

    ann_fstruct_delete(&fStruct);

    return 0;
}
