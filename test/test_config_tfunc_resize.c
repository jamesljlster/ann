#include <stdio.h>

#include <ann.h>

int main(int argc, char* argv[])
{
	int iResult;
	ann_config_t cfg;

	ann_config_create(&cfg);
	ann_config_set_inputs(cfg, 4);
	ann_config_set_outputs(cfg, 3);
	ann_config_set_transfer_func(cfg, 0);

	// Test cycle 1
	printf("Test cycle 1\n");
	iResult = ann_config_set_hidden_layers(cfg, 1);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_config_set_hidden_layers() failed\n");
		return -1;
	}

	iResult = ann_config_set_hidden_nodes(cfg, 0, 12);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_config_set_nodes() failed\n");
		return -1;
	}

	iResult = ann_config_set_transfer_func_of_layer(cfg, 2, ANN_SOFTPLUS);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_config_set_transfer_func_of_layer() failed with error: %s\n", ann_get_error_msg(iResult));
		return -1;
	}

	ann_config_print(cfg);

	// Test cycle 2
	printf("Test cycle 2\n");
	iResult = ann_config_set_hidden_layers(cfg, 5);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_config_set_hidden_layers() failed\n");
		return -1;
	}

	iResult = ann_config_set_hidden_nodes(cfg, 1, 16);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_config_set_nodes() failed\n");
		return -1;
	}

	iResult = ann_config_set_transfer_func_of_layer(cfg, 6, ANN_SOFTSIGN);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_config_set_transfer_func_of_layer() failed with error: %s\n", ann_get_error_msg(iResult));
		return -1;
	}

	ann_config_print(cfg);
	ann_config_delete(cfg);

	return 0;
}
