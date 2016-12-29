#include <stdio.h>

#include <ann.h>

int main(int argc, char* argv[])
{
	int i;
	int iResult;
	ann_config_t cfg;

	ann_config_create(&cfg);
	ann_config_set_inputs(cfg, 4);
	ann_config_set_outputs(cfg, 3);
	ann_config_set_transfer_func(cfg, 0);

	for(i = 0; i < 10; i++)
	{
		iResult = ann_config_set_hidden_layers(cfg, i);
		if(iResult != ANN_NO_ERROR)
		{
			printf("ann_config_set_hidden_layers() failed\n");
			return -1;
		}

		if(i > 0)
		{
			iResult = ann_config_set_hidden_nodes(cfg, i - 1, i);
			if(iResult != ANN_NO_ERROR)
			{
				printf("ann_config_set_nodes() failed\n");
				return -1;
			}
		}

		ann_config_print(cfg);
	}

	ann_config_delete(cfg);

	return 0;
}
