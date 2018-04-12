#include <stdio.h>

#include <ann.h>

int main(int argc, char* argv[])
{
	int iResult;
	ann_t ann;

	// Checking
	if(argc <= 1)
	{
		printf("Assign a .rnn file to run the program\n");
		return -1;
	}

	iResult = ann_import(&ann, argv[1]);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_import() failed with error: %d\n", iResult);
		return -1;
	}

	ann_print(ann);

	ann_delete(ann);

	return 0;
}
