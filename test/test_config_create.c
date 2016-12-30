#include <stdio.h>

#include <ann.h>

int main()
{
	int i;
	int iResult;
	ann_config_t cfg;

	iResult = ann_config_create_args(&cfg, 4, 3, 0, 0.01, 0.1, 5, 1, 2, 3, 4, 5);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_config_create() failed!\n");
		return -1;
	}

	ann_config_print(cfg);

	ann_config_delete(cfg);

	return 0;
}
