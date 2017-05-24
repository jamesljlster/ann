#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <ann.h>

#define INPUTS			2
#define OUTPUTS			1
#define HIDDEN_LAYER	1
#define HIDDEN_SIZE		16

#define L_RATE		0.001
#define M_COEF		0.1
#define DECAY		0.996
#define T_FUNC		ANN_SOFTSIGN

#define STOP_MSE	0.00001
#define ITER_COUNT	10000
#define DELTA_LIMIT	1

#define DATA_ROWS	256
#define DATA_COLS	8

double* adder_dataprep(int rows, int cols);

int main(int argc, char* argv[])
{
	int i, j, k;
	int augendIndex, addendIndex;
	int iResult;
	int iterCount;

	double lRate, mCoef;
	double mse;

	double* inputList[DATA_COLS];
	double* desireList[DATA_COLS];
	double* errList[DATA_COLS];

	clock_t timeHold;

	double* dataset;
	int dataRows, dataCols;

	ann_t ann = NULL;
	ann_config_t cfg = NULL;

	if(argc > 1)
	{
		iResult = ann_import(&ann, argv[1]);
		if(iResult != ANN_NO_ERROR)
		{
			printf("Failed to import neural network\n");
			return -1;
		}
	}
	else
	{
		// Create config
		iResult = ann_config_create(&cfg);
		if(iResult != ANN_NO_ERROR)
		{
			printf("ann_config_create() failed with error: %d\n", iResult);
			return -1;
		}

		ann_config_set_inputs(cfg, INPUTS);
		ann_config_set_outputs(cfg, OUTPUTS);
		ann_config_set_transfer_func(cfg, ANN_SIGMOID);
		ann_config_set_learning_rate(cfg, L_RATE);
		ann_config_set_momentum_coef(cfg, M_COEF);

		iResult = ann_config_set_hidden_layers(cfg, HIDDEN_LAYER);
		if(iResult != ANN_NO_ERROR)
		{
			printf("ann_config_set_hidden_layers() failed with error: %d\n", iResult);
			return -1;
		}

		for(i = 0; i < HIDDEN_LAYER; i++)
		{
			iResult = ann_config_set_hidden_nodes(cfg, 0, HIDDEN_SIZE);
			if(iResult != ANN_NO_ERROR)
			{
				printf("ann_config_set_nodes() failed with error: %d\n", iResult);
				return -1;
			}
		}

		// Create neural network
		iResult = ann_create(&ann, cfg);
		if(iResult != ANN_NO_ERROR)
		{
			printf("ann_create() failed with error: %d\n", iResult);
			return -1;
		}

		// Random weight and threshold
		ann_rand_weight(ann);
		ann_rand_threshold(ann);
	}

	// Prepare dataset
	dataRows = DATA_ROWS;
	dataCols = DATA_COLS;
	dataset = adder_dataprep(dataRows, dataCols);
	if(dataset == NULL)
	{
		printf("Prepare dataset failed!\n");
		return -1;
	}
	else
	{
		for(i = 0; i < dataRows; i++)
		{
			for(j = 0; j < dataCols; j++)
			{
				printf("%lf, ", dataset[i * dataCols + j]);
			}
			printf("\n");
		}
	}

	getchar();
	
	// Memory allocation
	for(i = 0; i < DATA_COLS; i++)
	{
		inputList[i] = calloc(INPUTS, sizeof(double));
		if(inputList[i] == NULL)
		{
			printf("Memory allocation failed!\n");
			return -1;
		}

		desireList[i] = calloc(OUTPUTS, sizeof(double));
		if(desireList[i] == NULL)
		{
			printf("Memory allocation failed!\n");
			return -1;
		}

		errList[i] = calloc(OUTPUTS, sizeof(double));
		if(errList[i] == NULL)
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
	while(iterCount < ITER_COUNT)
	{
		mse = 0;
		for(i = 0; i < DATA_ROWS - 2; i++)
		{
			// Set input and desire list
			for(j = 0; j < DATA_COLS; j++)
			{
				inputList[j][0] = dataset[i * DATA_COLS + j];
				inputList[j][1] = dataset[(i + 1) * DATA_COLS + j];
				desireList[j][0] = dataset[(i * 2 + 1) * DATA_COLS + j];
			}

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

			// Training
			iResult = rnn_training_gradient_custom(ann, lRate, mCoef, inputList, desireList, NULL, errList, DATA_COLS, DELTA_LIMIT);
			if(iResult != ANN_NO_ERROR)
			{
				printf("rnn_training_gradient() failed with error: %s\n", ann_get_error_msg(iResult));
				return -1;
			}

			rnn_forget(ann);

			// Find error
			for(j = 0; j < DATA_COLS; j++)
			{
				for(k = 0; k < OUTPUTS; k++)
				{
					mse += errList[j][k] * errList[j][k];
				}
			}
		}

		mse /= (double)(DATA_COLS) * (double)(DATA_ROWS - 2) * (double)OUTPUTS;
		printf("Iter. %5d mse: %lf\n", iterCount, mse);

		if(mse <= STOP_MSE)
			break;

		lRate = lRate * DECAY;
		mCoef = mCoef * DECAY;
		iterCount++;
	}

	timeHold = clock() - timeHold;

	ann_print(ann);

	printf("\nTime cost: %lf secs\n\n", (double)timeHold / (double)CLOCKS_PER_SEC);

	iResult = ann_export(ann, "./test.vgn");
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_export() failed!\n");
	}

	ann_delete(ann);
	ann_config_delete(cfg);

	return 0;
}

double* adder_dataprep(int rows, int cols)
{
	int i, j;

	double* tmpPtr = NULL;

	// Memory allocation
	tmpPtr = calloc(rows * cols, sizeof(double));
	if(tmpPtr == NULL)
	{
		goto RET;
	}

	// Prepare dataset
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if((i & (1 << j)) > 0)
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

