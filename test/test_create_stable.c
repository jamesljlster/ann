#include <stdio.h>

#include <ann.h>

int main(int argc, char* argv[])
{
    int iResult;
    ann_t ann;
    ann_config_t cfg;

    ann_config_create(&cfg);
    ann_config_set_inputs(cfg, 4);
    ann_config_set_outputs(cfg, 3);
    ann_config_set_hidden_layers(cfg, 10);
    ann_config_set_transfer_func(cfg, 0);

    while (1)
    {
        iResult = ann_create(&ann, cfg);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_create() failed with error: %d\n", iResult);
            return -1;
        }

        ann_delete(ann);
    }

    return 0;
}
