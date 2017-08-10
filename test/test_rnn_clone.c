
#include <stdio.h>

#include <ann.h>

int main(int argc, char* argv[])
{
	int iResult;
	ann_t ann;
	ann_t annClone;

	// Checking
	if(argc <= 1)
	{
		printf("Assign a rnn model file to run the program\n");
		return -1;
	}

	iResult = rnn_import(&ann, argv[1]);
	if(iResult != ANN_NO_ERROR)
	{
		printf("rnn_import() failed with error: %d\n", iResult);
		return -1;
	}

	iResult = ann_clone(&annClone, ann);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_clone() failed with error: %d\n", iResult);
		return -1;
	}

	iResult = rnn_export(annClone, "./test_rnn_clone.rnn");
	if(iResult != ANN_NO_ERROR)
	{
		printf("rnn_export() failed with error: %d\n", iResult);
		return -1;
	}

	printf("Cloned rnn:\n");
	rnn_print(annClone);

	ann_delete(annClone);
	ann_delete(ann);

	return 0;
}
