#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <ann.h>

#define INPUTS	1
#define OUTPUTS	1

int main(int argc, char* argv[])
{
	int i;
	int iResult;
	int hiddenSize, iter;
	double input = 0, err = 0;

	clock_t timeHold;

	ann_config_t cfg;
	ann_t ann;

	// Parse argument
	if(argc < 3)
	{
		printf("Usage: test_rnn_bptt_perf <hidden_size> <iteration>\n");
		return -1;
	}

	hiddenSize = atoi(argv[1]);
	iter = atoi(argv[2]);

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

	iResult = ann_config_set_hidden_nodes(cfg, 0, hiddenSize);
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

	// Set time step
	/*
	iResult = rnn_bptt_set_max_timestep(ann, 1);
	if(iResult != ANN_NO_ERROR)
	{
		printf("rnn_set_max_timestep() failed with error: %d\n", iResult);
		return -1;
	}
	*/

	// Test performance
	timeHold = clock();
	for(i = 0; i < iter; i++)
	{
		rnn_bptt_sum_gradient(ann, &err);
		rnn_bptt_erase(ann);
	}
	timeHold = clock() - timeHold;

	printf("Summary:\n");
	printf("    Hidden Size: %d\n", hiddenSize);
	printf("    BP Iteration: %d\n", iter);
	printf("    Time Cost: %lf\n", (double)timeHold / (double)CLOCKS_PER_SEC);

	return 0;
}
