#include <stdio.h>

#include <ann.h>
#include <ann_parse.h>
#include <ann_print.h>
#include <ann_private.h>
#include <ann_file_proc.h>

int main(int argc, char* argv[])
{
	int iResult;
	
	struct ANN_STRUCT annStruct;
	struct ANN_FILE_STRUCT fStruct;

	ann_zeromem(&annStruct);
	
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

	iResult = ann_parse_config(&annStruct.config, &fStruct);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_config_parse() failed with error: %d\n", iResult);
		return -1;
	}

	iResult = ann_parse_network(&annStruct, &fStruct, ANN_NETWORK_ANN);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_parse_network() failed with error: %d\n", iResult);
		return -1;
	}

	ann_fprint_threshold(stdout, &annStruct);
	ann_fprint_weight(stdout, &annStruct);

	return 0;
}
