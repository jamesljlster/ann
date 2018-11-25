#include <stdio.h>

#include <ann.h>

int main()
{
    int i;
    int iResult;
    ann_config_t cfg;

    while (1)
    {
        iResult = ann_config_create(&cfg);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_config_create() failed!\n");
            return -1;
        }

        for (i = 1; i < 1000; i++)
        {
            iResult = ann_config_set_hidden_layers(cfg, i);
            if (iResult != ANN_NO_ERROR)
            {
                printf("ann_set_hidden_layers() failed!\n");
            }
        }

        ann_config_delete(cfg);
    }

    return 0;
}
