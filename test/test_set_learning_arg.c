#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <ann.h>

#define INPUTS		4
#define OUTPUTS		3
#define ITER_COUNT	10000
#define DATA_AMOUNT	120

extern double dataset[];

int main(int argc, char* argv[])
{
	int i, j;
	int iResult;
	int iterCount;

	double lRate = 0.01;
	double mCoef = 0.1;

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

		iResult = ann_config_set_hidden_nodes(cfg, 0, 12);
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
			iResult = ann_training_gradient(ann, &dataset[i * (INPUTS + OUTPUTS)], &dataset[i * (INPUTS + OUTPUTS) + INPUTS], NULL, err);
			if(iResult != ANN_NO_ERROR)
			{
				printf("ann_training_gradient() failed with error: %d\n", iResult);
				return -1;
			}
			
			for(j = 0; j < OUTPUTS; j++)
				iterErr[j] += err[j];
		}

		for(i = 0; i < OUTPUTS; i++)
			iterErr[i] /= (double)DATA_AMOUNT;

		printf("Iter. %5d error list: ", iterCount);
		for(i = 0; i < OUTPUTS; i++)
		{
			printf("%lf, ", iterErr[i]);
		}
		printf("lRate: %lf, mCoef: %lf\n", ann_get_learning_rate(ann), ann_get_momentum_coef(ann));

		// Update learning arguments
		lRate = lRate * 0.999;
		mCoef = mCoef * 0.999;
		ann_set_learning_rate(ann, lRate);
		ann_set_momentum_coef(ann, mCoef);

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
	5.1, 3.5, 1.4, 0.2, 1.0, 0.0, 0.0,
	4.9, 3.0, 1.4, 0.2, 1.0, 0.0, 0.0,
	4.6, 3.1, 1.5, 0.2, 1.0, 0.0, 0.0,
	5.0, 3.6, 1.4, 0.2, 1.0, 0.0, 0.0,
	5.4, 3.9, 1.7, 0.4, 1.0, 0.0, 0.0,
	5.0, 3.4, 1.5, 0.2, 1.0, 0.0, 0.0,
	4.4, 2.9, 1.4, 0.2, 1.0, 0.0, 0.0,
	4.8, 3.4, 1.6, 0.2, 1.0, 0.0, 0.0,
	4.8, 3.0, 1.4, 0.1, 1.0, 0.0, 0.0,
	4.3, 3.0, 1.1, 0.1, 1.0, 0.0, 0.0,
	5.7, 4.4, 1.5, 0.4, 1.0, 0.0, 0.0,
	5.4, 3.9, 1.3, 0.4, 1.0, 0.0, 0.0,
	5.1, 3.5, 1.4, 0.3, 1.0, 0.0, 0.0,
	5.4, 3.4, 1.7, 0.2, 1.0, 0.0, 0.0,
	5.1, 3.7, 1.5, 0.4, 1.0, 0.0, 0.0,
	4.6, 3.6, 1.0, 0.2, 1.0, 0.0, 0.0,
	5.1, 3.3, 1.7, 0.5, 1.0, 0.0, 0.0,
	4.8, 3.4, 1.9, 0.2, 1.0, 0.0, 0.0,
	5.0, 3.0, 1.6, 0.2, 1.0, 0.0, 0.0,
	5.0, 3.4, 1.6, 0.4, 1.0, 0.0, 0.0,
	5.2, 3.5, 1.5, 0.2, 1.0, 0.0, 0.0,
	5.2, 3.4, 1.4, 0.2, 1.0, 0.0, 0.0,
	4.7, 3.2, 1.6, 0.2, 1.0, 0.0, 0.0,
	4.8, 3.1, 1.6, 0.2, 1.0, 0.0, 0.0,
	5.4, 3.4, 1.5, 0.4, 1.0, 0.0, 0.0,
	5.2, 4.1, 1.5, 0.1, 1.0, 0.0, 0.0,
	5.5, 4.2, 1.4, 0.2, 1.0, 0.0, 0.0,
	5.0, 3.2, 1.2, 0.2, 1.0, 0.0, 0.0,
	5.5, 3.5, 1.3, 0.2, 1.0, 0.0, 0.0,
	5.1, 3.4, 1.5, 0.2, 1.0, 0.0, 0.0,
	5.0, 3.5, 1.3, 0.3, 1.0, 0.0, 0.0,
	4.5, 2.3, 1.3, 0.3, 1.0, 0.0, 0.0,
	5.1, 3.8, 1.9, 0.4, 1.0, 0.0, 0.0,
	4.8, 3.0, 1.4, 0.3, 1.0, 0.0, 0.0,
	4.6, 3.2, 1.4, 0.2, 1.0, 0.0, 0.0,
	5.3, 3.7, 1.5, 0.2, 1.0, 0.0, 0.0,
	5.0, 3.3, 1.4, 0.2, 1.0, 0.0, 0.0,
	7.0, 3.2, 4.7, 1.4, 0.0, 1.0, 0.0,
	6.4, 3.2, 4.5, 1.5, 0.0, 1.0, 0.0,
	6.9, 3.1, 4.9, 1.5, 0.0, 1.0, 0.0,
	5.5, 2.3, 4.0, 1.3, 0.0, 1.0, 0.0,
	6.3, 3.3, 4.7, 1.6, 0.0, 1.0, 0.0,
	4.9, 2.4, 3.3, 1.0, 0.0, 1.0, 0.0,
	6.0, 2.2, 4.0, 1.0, 0.0, 1.0, 0.0,
	6.1, 2.9, 4.7, 1.4, 0.0, 1.0, 0.0,
	5.6, 2.9, 3.6, 1.3, 0.0, 1.0, 0.0,
	6.7, 3.1, 4.4, 1.4, 0.0, 1.0, 0.0,
	5.6, 3.0, 4.5, 1.5, 0.0, 1.0, 0.0,
	5.8, 2.7, 4.1, 1.0, 0.0, 1.0, 0.0,
	6.2, 2.2, 4.5, 1.5, 0.0, 1.0, 0.0,
	5.6, 2.5, 3.9, 1.1, 0.0, 1.0, 0.0,
	5.9, 3.2, 4.8, 1.8, 0.0, 1.0, 0.0,
	6.1, 2.8, 4.0, 1.3, 0.0, 1.0, 0.0,
	6.3, 2.5, 4.9, 1.5, 0.0, 1.0, 0.0,
	6.1, 2.8, 4.7, 1.2, 0.0, 1.0, 0.0,
	6.4, 2.9, 4.3, 1.3, 0.0, 1.0, 0.0,
	6.6, 3.0, 4.4, 1.4, 0.0, 1.0, 0.0,
	6.7, 3.0, 5.0, 1.7, 0.0, 1.0, 0.0,
	5.7, 2.6, 3.5, 1.0, 0.0, 1.0, 0.0,
	5.5, 2.4, 3.7, 1.0, 0.0, 1.0, 0.0,
	5.8, 2.7, 3.9, 1.2, 0.0, 1.0, 0.0,
	6.0, 2.7, 5.1, 1.6, 0.0, 1.0, 0.0,
	5.4, 3.0, 4.5, 1.5, 0.0, 1.0, 0.0,
	6.7, 3.1, 4.7, 1.5, 0.0, 1.0, 0.0,
	6.3, 2.3, 4.4, 1.3, 0.0, 1.0, 0.0,
	5.5, 2.6, 4.4, 1.2, 0.0, 1.0, 0.0,
	6.1, 3.0, 4.6, 1.4, 0.0, 1.0, 0.0,
	5.8, 2.6, 4.0, 1.2, 0.0, 1.0, 0.0,
	5.0, 2.3, 3.3, 1.0, 0.0, 1.0, 0.0,
	5.6, 2.7, 4.2, 1.3, 0.0, 1.0, 0.0,
	5.7, 3.0, 4.2, 1.2, 0.0, 1.0, 0.0,
	5.7, 2.9, 4.2, 1.3, 0.0, 1.0, 0.0,
	6.2, 2.9, 4.3, 1.3, 0.0, 1.0, 0.0,
	6.3, 3.3, 6.0, 2.5, 0.0, 0.0, 1.0,
	5.8, 2.7, 5.1, 1.9, 0.0, 0.0, 1.0,
	7.1, 3.0, 5.9, 2.1, 0.0, 0.0, 1.0,
	6.5, 3.0, 5.8, 2.2, 0.0, 0.0, 1.0,
	7.6, 3.0, 6.6, 2.1, 0.0, 0.0, 1.0,
	4.9, 2.5, 4.5, 1.7, 0.0, 0.0, 1.0,
	7.3, 2.9, 6.3, 1.8, 0.0, 0.0, 1.0,
	6.7, 2.5, 5.8, 1.8, 0.0, 0.0, 1.0,
	6.5, 3.2, 5.1, 2.0, 0.0, 0.0, 1.0,
	6.4, 2.7, 5.3, 1.9, 0.0, 0.0, 1.0,
	6.8, 3.0, 5.5, 2.1, 0.0, 0.0, 1.0,
	5.8, 2.8, 5.1, 2.4, 0.0, 0.0, 1.0,
	6.4, 3.2, 5.3, 2.3, 0.0, 0.0, 1.0,
	7.7, 3.8, 6.7, 2.2, 0.0, 0.0, 1.0,
	5.6, 2.8, 4.9, 2.0, 0.0, 0.0, 1.0,
	7.7, 2.8, 6.7, 2.0, 0.0, 0.0, 1.0,
	6.3, 2.7, 4.9, 1.8, 0.0, 0.0, 1.0,
	6.7, 3.3, 5.7, 2.1, 0.0, 0.0, 1.0,
	7.2, 3.2, 6.0, 1.8, 0.0, 0.0, 1.0,
	6.1, 3.0, 4.9, 1.8, 0.0, 0.0, 1.0,
	6.4, 2.8, 5.6, 2.1, 0.0, 0.0, 1.0,
	6.4, 2.8, 5.6, 2.2, 0.0, 0.0, 1.0,
	6.3, 2.8, 5.1, 1.5, 0.0, 0.0, 1.0,
	6.1, 2.6, 5.6, 1.4, 0.0, 0.0, 1.0,
	7.7, 3.0, 6.1, 2.3, 0.0, 0.0, 1.0,
	6.3, 3.4, 5.6, 2.4, 0.0, 0.0, 1.0,
	6.4, 3.1, 5.5, 1.8, 0.0, 0.0, 1.0,
	6.0, 3.0, 4.8, 1.8, 0.0, 0.0, 1.0,
	6.9, 3.1, 5.4, 2.1, 0.0, 0.0, 1.0,
	6.7, 3.1, 5.6, 2.4, 0.0, 0.0, 1.0,
	6.9, 3.1, 5.1, 2.3, 0.0, 0.0, 1.0,
	6.8, 3.2, 5.9, 2.3, 0.0, 0.0, 1.0,
	6.7, 3.3, 5.7, 2.5, 0.0, 0.0, 1.0,
	6.5, 3.0, 5.2, 2.0, 0.0, 0.0, 1.0,
	6.2, 3.4, 5.4, 2.3, 0.0, 0.0, 1.0,
	5.9, 3.0, 5.1, 1.8, 0.0, 0.0, 1.0,
	4.7, 3.2, 1.3, 0.2, 1.0, 0.0, 0.0,
	5.8, 4.0, 1.2, 0.2, 1.0, 0.0, 0.0,
	4.4, 3.2, 1.3, 0.2, 1.0, 0.0, 0.0,
	6.6, 2.9, 4.6, 1.3, 0.0, 1.0, 0.0,
	6.8, 2.8, 4.8, 1.4, 0.0, 1.0, 0.0,
	6.0, 2.9, 4.5, 1.5, 0.0, 1.0, 0.0,
	6.0, 3.4, 4.5, 1.6, 0.0, 1.0, 0.0,
	6.5, 3.0, 5.5, 1.8, 0.0, 0.0, 1.0,
	6.0, 2.2, 5.0, 1.5, 0.0, 0.0, 1.0,
	6.9, 3.2, 5.7, 2.3, 0.0, 0.0, 1.0,
	6.2, 2.8, 4.8, 1.8, 0.0, 0.0, 1.0
};
