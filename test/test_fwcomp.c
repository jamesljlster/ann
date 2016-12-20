#include <stdio.h>
#include <stdlib.h>

#include <ann.h>

int main(int argc, char* argv[])
{
	int i;
	int iResult;
	int inputs, outputs;

	ann_t ann;
	ann_config_t cfg;

	double* input = NULL;
	double* output = NULL;

	// Checking
	if(argc <= 1)
	{
		printf("Assign a .vgn file to run the program\n");
		return -1;
	}

	iResult = ann_import(&ann, argv[1]);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_import() failed with error: %d\n", iResult);
		return -1;
	}

	// Get neural network configuration
	cfg = ann_get_config(ann);
	inputs = ann_config_get_inputs(cfg);
	outputs = ann_config_get_outputs(cfg);

	// Memory allocation
	input = calloc(inputs, sizeof(double));
	output = calloc(outputs, sizeof(double));
	if(input == NULL || output == NULL)
	{
		printf("Memory allocation failed\n");
		return -1;
	}
	
	for(i = 0; i < inputs; i++)
	{
		printf("Assign %d of %d input: ", i + 1, inputs);
		scanf(" %lf", &input[i]);
	}

	iResult = ann_forward_computation(ann, input, output);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_forward_compution() failed with error: %d\n", iResult);
		return -1;
	}

	for(i = 0; i < outputs; i++)
	{
		printf("%d of %d output: %G\n", i + 1, outputs, output[i]);
	}

	ann_delete(ann);

	return 0;
}
