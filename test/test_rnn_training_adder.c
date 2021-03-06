#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <ann.h>

#define INPUTS 2
#define OUTPUTS 1
#define HIDDEN_LAYER 1
#define HIDDEN_SIZE 16

#define L_RATE 0.01
#define M_COEF 0.1
#define DECAY 1.0
#define T_FUNC ANN_SOFTSIGN

#define STOP_MSE 0.001
#define ITER_COUNT 10000
#define DELTA_LIMIT 30

#define DATA_ROWS 256
#define DATA_COLS 8
#define RAND_SWAP 32768

//#define DEBUG

float* adder_dataprep(int rows, int cols);

int main(int argc, char* argv[])
{
    int i, j, k;
    int augendIndex, addendIndex;
    int dataCounter;
    int iResult;
    int iterCount;

    float lRate, mCoef;
    float mse;

    float* inputList[DATA_COLS];
    float* desireList[DATA_COLS];
    float* errList[DATA_COLS];

    clock_t timeHold;

    float* dataset;
    int dataRows, dataCols;

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
        ann_config_set_transfer_func(cfg, T_FUNC);
        ann_config_set_learning_rate(cfg, L_RATE);
        ann_config_set_momentum_coef(cfg, M_COEF);

        iResult = ann_config_set_hidden_layers(cfg, HIDDEN_LAYER);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_config_set_hidden_layers() failed with error: %d\n",
                   iResult);
            return -1;
        }

        for (i = 0; i < HIDDEN_LAYER; i++)
        {
            iResult = ann_config_set_hidden_nodes(cfg, i, HIDDEN_SIZE);
            if (iResult != ANN_NO_ERROR)
            {
                printf("ann_config_set_nodes() failed with error: %d\n",
                       iResult);
                return -1;
            }
        }

        iResult = ann_config_set_transfer_func_of_layer(cfg, 0, ANN_IDENTITY);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_config_set_hidden_layers() failed with error: %d\n",
                   iResult);
            return -1;
        }

        // Create neural network
        iResult = ann_create(&ann, cfg);
        if (iResult != ANN_NO_ERROR)
        {
            printf("ann_create() failed with error: %d\n", iResult);
            return -1;
        }

        // Random weight and threshold
        ann_rand_weight(ann);
        ann_rand_threshold(ann);
        rnn_rand_recurrent_weight(ann);
    }

    // Prepare dataset
    dataRows = DATA_ROWS;
    dataCols = DATA_COLS;
    dataset = adder_dataprep(dataRows, dataCols);
    if (dataset == NULL)
    {
        printf("Prepare dataset failed!\n");
        return -1;
    }
#ifdef DEBUG
    else
    {
        for (i = 0; i < dataRows; i++)
        {
            for (j = 0; j < dataCols; j++)
            {
                printf("%lf, ", dataset[i * dataCols + j]);
            }
            printf("\n");
        }
    }
    getchar();
#endif

    // Memory allocation
    for (i = 0; i < DATA_COLS; i++)
    {
        inputList[i] = calloc(INPUTS, sizeof(float));
        if (inputList[i] == NULL)
        {
            printf("Memory allocation failed!\n");
            return -1;
        }

        desireList[i] = calloc(OUTPUTS, sizeof(float));
        if (desireList[i] == NULL)
        {
            printf("Memory allocation failed!\n");
            return -1;
        }

        errList[i] = calloc(OUTPUTS, sizeof(float));
        if (errList[i] == NULL)
        {
            printf("Memory allocaton failed!\n");
            return -1;
        }
    }

    // Training
    timeHold = 0;
    iterCount = 0;
    lRate = L_RATE;
    mCoef = M_COEF;
    while (iterCount < ITER_COUNT)
    {
        mse = 0;
        dataCounter = 0;
        for (augendIndex = 0; augendIndex < dataRows - 1; augendIndex++)
        {
            for (addendIndex = augendIndex + 1; addendIndex < dataRows;
                 addendIndex++)
            {
                if (augendIndex + addendIndex < dataRows)
                {
                    // Set input and desire list
                    for (j = 0; j < DATA_COLS; j++)
                    {
                        inputList[j][0] = dataset[augendIndex * DATA_COLS + j];
                        inputList[j][1] = dataset[addendIndex * DATA_COLS + j];
                        desireList[j][0] =
                            dataset[(augendIndex + addendIndex) * DATA_COLS +
                                    j];
                    }

#ifdef DEBUG
                    // Print data
                    printf("Input list: \n");
                    for (j = DATA_COLS - 1; j >= 0; j--)
                    {
                        printf("%lf ", inputList[j][0]);
                    }
                    printf("\n");

                    for (j = DATA_COLS - 1; j >= 0; j--)
                    {
                        printf("%lf ", inputList[j][1]);
                    }
                    printf("\n");

                    printf("Output list: \n");
                    for (j = DATA_COLS - 1; j >= 0; j--)
                    {
                        printf("%lf ", desireList[j][0]);
                    }
                    printf("\n");
                    getchar();
#endif

                    // Training
                    iResult = rnn_training_gradient_custom(
                        ann, lRate, mCoef, inputList, desireList, NULL, errList,
                        DATA_COLS, DELTA_LIMIT);
                    if (iResult != ANN_NO_ERROR)
                    {
                        printf(
                            "rnn_training_gradient() failed with error: %s\n",
                            ann_get_error_msg(iResult));
                        return -1;
                    }

                    // Find error
                    for (j = 0; j < DATA_COLS; j++)
                    {
                        for (k = 0; k < OUTPUTS; k++)
                        {
                            mse += errList[j][k] * errList[j][k];
                        }
                    }

                    dataCounter++;
                }
            }
        }

        /*
                for(i = 0; i < dataRows - 1; i++)
                {
                    if(dataIndex[i] + dataIndex[i + 1] < DATA_ROWS)
                    {
                        // Set input and desire list
                        for(j = 0; j < DATA_COLS; j++)
                        {
                            inputList[j][0] = dataset[dataIndex[i] * DATA_COLS +
        j]; inputList[j][1] = dataset[dataIndex[i + 1] * DATA_COLS + j];
                            desireList[j][0] = dataset[(dataIndex[i] +
        dataIndex[i + 1]) * DATA_COLS + j];
                        }

        #ifdef DEBUG
                        // Print data
                        printf("Input list: \n");
                        for(j = DATA_COLS - 1; j >= 0; j--)
                        {
                            printf("%lf ", inputList[j][0]);
                        }
                        printf("\n");

                        for(j = DATA_COLS - 1; j >= 0; j--)
                        {
                            printf("%lf ", inputList[j][1]);
                        }
                        printf("\n");

                        printf("Output list: \n");
                        for(j = DATA_COLS - 1; j >= 0; j--)
                        {
                            printf("%lf ", desireList[j][0]);
                        }
                        printf("\n");
                        getchar();
        #endif

                        // Training
                        iResult = rnn_training_gradient_custom(ann, lRate,
        mCoef, inputList, desireList, NULL, errList, DATA_COLS, DELTA_LIMIT);
                        if(iResult != ANN_NO_ERROR)
                        {
                            printf("rnn_training_gradient() failed with error:
        %s\n", ann_get_error_msg(iResult)); return -1;
                        }

                        // Find error
                        for(j = 0; j < DATA_COLS; j++)
                        {
                            for(k = 0; k < OUTPUTS; k++)
                            {
                                mse += errList[j][k] * errList[j][k];
                            }
                        }

                        dataCounter++;
                    }
                }
        */

        mse /= (float)(DATA_COLS) * (float)(dataCounter) * (float)OUTPUTS;
        printf("Iter. %5d mse: %lf\n", iterCount, mse);

        if (mse <= STOP_MSE) break;

        lRate = lRate * DECAY;
        mCoef = mCoef * DECAY;
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

float* adder_dataprep(int rows, int cols)
{
    int i, j;

    float* tmpPtr = NULL;

    // Memory allocation
    tmpPtr = calloc(rows * cols, sizeof(float));
    if (tmpPtr == NULL)
    {
        goto RET;
    }

    // Prepare dataset
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if ((i & (1 << j)) > 0)
            {
                tmpPtr[i * cols + j] = 1;
            }
            else
            {
                tmpPtr[i * cols + j] = 0;
            }
        }
    }

RET:
    return tmpPtr;
}
