#include <stdio.h>

#include <ann.h>
#include <ann_private.h>

int main(int argc, char* argv[])
{
	int iResult;

	struct ANN_FILE_STRUCT fStruct;
	struct ANN_CONFIG_STRUCT cfgTmp;
	
	// Checking
	if(argc <= 1)
	{
		printf("Assign a .vgn file to run the program.\n");
		return -1;
	}
	
	iResult = ann_fstruct_create(&fStruct, argv[1]);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_fstruct_create() failed\n");
		return -1;
	}

	iResult = ann_parse_config(&cfgTmp, &fStruct);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_config_parse() failed with error: %d\n", iResult);
		return -1;
	}

	ann_config_print_struct(&cfgTmp);

	return 0;
}
