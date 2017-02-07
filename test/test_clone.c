
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
		printf("Assign a .vgn file to run the program\n");
		return -1;
	}

	iResult = ann_import(&ann, argv[1]);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_import() failed with error: %d\n", iResult);
		return -1;
	}

	iResult = ann_clone(&annClone, ann);
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_clone() failed with error: %d\n", iResult);
		return -1;
	}

	iResult = ann_export(annClone, "./test_clone.vgn");
	if(iResult != ANN_NO_ERROR)
	{
		printf("ann_export() failed with error: %d\n", iResult);
		return -1;
	}

	printf("Cloned ann:\n");
	ann_print(annClone);

	ann_delete(annClone);
	ann_delete(ann);

	return 0;
}
