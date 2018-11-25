#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <ann.h>

#define INPUTS 1
#define OUTPUTS 1
#define ITER_COUNT 2
#define DATA_AMOUNT 3
#define DELTA_LIMIT 100

#define DEBUG

extern float dataset[];

int main(int argc, char* argv[])
{
    int i, j;
    int iResult;
    int iterCount;

    float outputList[OUTPUTS];
    float err[OUTPUTS];
    float iterErr[OUTPUTS];

    clock_t timeHold;

    ann_t ann = NULL;
    ann_config_t cfg = NULL;

    if (argc > 1)
    {
        iResult = rnn_import(&ann, argv[1]);
        if (iResult != ANN_NO_ERROR)
        {
            printf("Failed to import neural network\n");
            return -1;
        }
    }
    else
    {
        // Create config
        iResult = ann_config_create(&cfg);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_config_create() failed with error: %d\n", iResult);
            return -1;
        }

        ann_config_set_inputs(cfg, INPUTS);
        ann_config_set_outputs(cfg, OUTPUTS);
        ann_config_set_transfer_func(cfg, ANN_SIGMOID);
        ann_config_set_learning_rate(cfg, 0.01);
        ann_config_set_momentum_coef(cfg, 0.1);

        iResult = ann_config_set_hidden_layers(cfg, 1);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_config_set_hidden_layers() failed with error: %d\n",
                   iResult);
            return -1;
        }

        iResult = ann_config_set_hidden_nodes(cfg, 0, 1);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_config_set_nodes() failed with error: %d\n", iResult);
            return -1;
        }

        // Create neural network
        iResult = ann_create(&ann, cfg);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_create() failed with error: %d\n", iResult);
            return -1;
        }

        // Test rnn functions
        rnn_set_recurrent_weight(ann, 0, 0, 0.5);
        printf("Recurrent of 0-0: %lf\n", rnn_get_recurrent_weight(ann, 0, 0));

        rnn_zero_recurrent_weight(ann);

        // Random weight and threshold
        ann_rand_weight(ann);
        ann_rand_threshold(ann);
        rnn_rand_recurrent_weight(ann);
    }

    // Set time step
    iResult = rnn_bptt_set_max_timestep(ann, DATA_AMOUNT);
    if (iResult != ANN_NO_ERROR)
    {
        printf("rnn_set_max_timestep() failed with error: %d\n", iResult);
        return -1;
    }

    // Training
    timeHold = 0;
    iterCount = 0;
    while (iterCount < ITER_COUNT)
    {
        for (i = 0; i < OUTPUTS; i++) iterErr[i] = 0;

        for (i = 0; i < DATA_AMOUNT; i++)
        {
            // Forward computation
            rnn_forward_computation(ann, &dataset[i * (INPUTS + OUTPUTS)],
                                    outputList);

            // Find error
            for (j = 0; j < OUTPUTS; j++)
                err[j] = dataset[i * (INPUTS + OUTPUTS) + INPUTS + j] -
                         outputList[j];

#ifdef DEBUG
            printf("Inputs: ");
            for (j = 0; j < INPUTS; j++)
            {
                printf("%lf, ", dataset[i * (INPUTS + OUTPUTS) + j]);
            }
            printf("\nOutputs: ");
            for (j = 0; j < OUTPUTS; j++)
            {
                printf("%lf, ", outputList[j]);
            }
            printf("\ndError: ");
            for (j = 0; j < OUTPUTS; j++)
            {
                printf("%lf, ", err[j]);
            }
            printf("\n\n");
#endif

            // Backpropagation
            rnn_bptt_sum_gradient(ann, err);

            // Find iteration error
            for (j = 0; j < OUTPUTS; j++) iterErr[j] += err[j];
        }

        // Adjust netwrok
        rnn_bptt_adjust_network(ann, 0.1, 0.0, DELTA_LIMIT);

        // Erase rnn
        rnn_bptt_erase(ann);
        rnn_forward_computation_erase(ann);

#ifdef DEBUG
        rnn_print(ann);
        getchar();
#endif

        for (i = 0; i < OUTPUTS; i++) iterErr[i] /= (float)DATA_AMOUNT;

        printf("Iter. %5d error list: ", iterCount);
        for (i = 0; i < OUTPUTS; i++)
        {
            printf("%lf, ", iterErr[i]);
        }
        printf("\n");

        iterCount++;
    }

    timeHold = clock() - timeHold;

    rnn_print(ann);

    printf("\nTime cost: %lf secs\n\n",
           (float)timeHold / (float)CLOCKS_PER_SEC);

    iResult = rnn_export(ann, "./test.vgn");
    if (iResult != ANN_NO_ERROR)
    {
        printf("ann_export() failed!\n");
    }

    ann_delete(ann);
    ann_config_delete(cfg);

    return 0;
}

float dataset[] = {
    0, 1,  //
    1, 0,  //
    0, 1   //
};
