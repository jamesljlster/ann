#include <stdio.h>
#include <stdlib.h>

#include <ann.h>

#define L_RATE 0.01
#define M_COEF 0.1

#define ann_run(func)                                         \
    {                                                         \
        int ret = func;                                       \
        if (ret != ANN_NO_ERROR)                              \
        {                                                     \
            printf("%s failed with error: %d\n", #func, ret); \
            return -1;                                        \
        }                                                     \
    }

int main(int argc, char* argv[])
{
    int i;
    int inputs, outputs;
    int hLayers, hNodes;

    ann_t ann;
    ann_config_t cfg;

    // Parse config
    if (argc < 5)
    {
        printf(
            "Usage: test_rnn_rand <inputs> <outputs> <hidden_layers> "
            "<hidden_nodes>\n");
        return -1;
    }
    else
    {
        inputs = atoi(argv[1]);
        outputs = atoi(argv[2]);
        hLayers = atoi(argv[3]);
        hNodes = atoi(argv[4]);
    }

    // Create config
    ann_run(ann_config_create(&cfg));
    ann_run(ann_config_set_inputs(cfg, inputs));
    ann_run(ann_config_set_outputs(cfg, outputs));
    ann_run(ann_config_set_hidden_layers(cfg, hLayers));
    for (int i = 0; i < hLayers; i++)
    {
        ann_run(ann_config_set_hidden_nodes(cfg, i, hNodes));
    }
    ann_run(ann_config_set_transfer_func(cfg, ANN_SIGMOID));
    ann_run(ann_config_set_transfer_func_of_layer(cfg, 0, ANN_IDENTITY));

    ann_config_set_learning_rate(cfg, L_RATE);
    ann_config_set_momentum_coef(cfg, M_COEF);

    // Create and export rnn
    ann_run(ann_create(&ann, cfg));
    ann_rand_network(ann);

    ann_run(rnn_export(ann, "test_rnn_rand.rnn"));

    return 0;
}
