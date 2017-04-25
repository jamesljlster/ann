#include <stdio.h>
#include <ann.h>

int main()
{
	int iResult;
	ann_t ann;
	
	iResult = ann_create_args(&ann, 4, 3, 0, 0.01, 0.1, 5, 1, 2, 3, 4, 5);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_create_args() failed!\n");
		return -1;
	}

	ann_print(ann);

	iResult = ann_export(ann, "./test_export.rnn");
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_export() failed!\n");
		return -1;
	}

	ann_delete(ann);
	return 0;
}
