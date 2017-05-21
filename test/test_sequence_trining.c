#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <ann.h>

#define INPUTS		1
#define OUTPUTS		1
#define ITER_COUNT	10000
#define DATA_AMOUNT	3

extern double dataset[];

int main(int argc, char* argv[])
{
	int i, j;
	int iResult;
	int iterCount;

	double outputList[OUTPUTS];
	double err[OUTPUTS];
	double iterErr[OUTPUTS];

	clock_t timeHold;

	ann_t ann;
	ann_config_t cfg;

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
		ann_config_set_learning_rate(cfg, 0.01);
		ann_config_set_momentum_coef(cfg, 0.1);

		iResult = ann_config_set_hidden_layers(cfg, 1);
		if(iResult != ANN_NO_ERROR)
		{
			printf("ann_config_set_hidden_layers() failed with error: %d\n", iResult);
			return -1;
		}

		iResult = ann_config_set_hidden_nodes(cfg, 0, 1);
		if(iResult != ANN_NO_ERROR)
		{
			printf("ann_config_set_nodes() failed with error: %d\n", iResult);
			return -1;
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

	// Training
	timeHold = 0;
	iterCount = 0;
	while(iterCount < ITER_COUNT)
	{
		for(i = 0; i < OUTPUTS; i++)
			iterErr[i] = 0;

		for(i = 0; i < DATA_AMOUNT; i++)
		{
			// Forward computation
			ann_forward_computation(ann, &dataset[i * (INPUTS + OUTPUTS)], outputList);

			// Find error
			for(j = 0; j < OUTPUTS; j++)
				err[j] = dataset[i * (INPUTS + OUTPUTS) + INPUTS + j] - outputList[i];

			// Backpropagation
			iResult = rnn_bptt_sum_delta(ann, err);
			if(iResult != ANN_NO_ERROR)
			{
				printf("rnn_bptt_sum_delta() failed with error: %d\n", iResult);
				return -1;
			}

			// Find iteration error
			for(j = 0; j < OUTPUTS; j++)
				iterErr[j] += err[j];
		}

		// Adjust netwrok
		rnn_bptt_adjust_network(ann, 0.01, 0.1);

		// Erase rnn
		rnn_bptt_erase(ann);
		rnn_forget(ann);

		for(i = 0; i < OUTPUTS; i++)
			iterErr[i] /= (double)DATA_AMOUNT;

		printf("Iter. %5d error list: ", iterCount);
		for(i = 0; i < OUTPUTS; i++)
		{
			printf("%lf, ", iterErr[i]);
		}
		printf("\n");

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

double dataset[] = {
	1, 0,
	0, 0,
	1, 1
};

