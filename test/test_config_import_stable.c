#include <stdio.h>

#include <ann.h>

int main(int argc, char* argv[])
{
	int iResult;
	ann_config_t annCfg;

	// Checking
	if(argc <= 1)
	{
		printf("Assign a .vgn file to run the program\n");
		return -1;
	}
	
	while(1)
	{
		iResult = ann_config_import(&annCfg, argv[1]);
		if(iResult != ANN_NO_ERROR)
		{
			printf("ann_config_import() failed with error: %d\n", iResult);
			return -1;
		}

		ann_config_delete(annCfg);
	}

	return 0;
}
