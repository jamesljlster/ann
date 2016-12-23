#include <stdio.h>

#include <ann.h>

int main(int argc, char* argv[])
{
	int i;
	int iResult;
	ann_t ann;
	ann_config_t cfg;

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

	cfg = ann_get_config(ann);

	printf("inputs: %d\n", ann_config_get_inputs(cfg));
	printf("outputs: %d\n", ann_config_get_outputs(cfg));
	printf("hidden layers: %d\n", ann_config_get_hidden_layers(cfg));
	printf("hidden nodes: ");
	for(i = 0; i < ann_config_get_hidden_layers(cfg); i++)
	{
		printf("%d, ", ann_config_get_hidden_nodes(cfg, i));
	}
	printf("\n");
	printf("transfer function index: %d\n", ann_config_get_transfer_func(cfg));
	printf("learning rate: %lf\n", ann_config_get_learning_rate(cfg));
	printf("momentum coef: %lf\n", ann_config_get_momentum_coef(cfg));

	ann_delete(ann);

	return 0;
}
