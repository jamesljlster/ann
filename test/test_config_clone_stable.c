#include <stdio.h>

#include <ann.h>

int main(int argc, char* argv[])
{
    int iResult;
    ann_config_t annCfg;
    ann_config_t tmpCfg;

    // Checking
    if (argc <= 1)
    {
        printf("Assign a .vgn file to run the program\n");
        return -1;
    }

    while (1)
    {
        iResult = ann_config_import(&annCfg, argv[1]);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_config_import() failed with error: %d\n", iResult);
            continue;
        }

        iResult = ann_config_clone(&tmpCfg, annCfg);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_config_clone() failed with error: %d\n", iResult);
            continue;
        }

        ann_config_delete(tmpCfg);
    }

    ann_config_delete(annCfg);

    return 0;
}
