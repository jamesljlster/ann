#include <stdio.h>
#include <ann.h>

int main()
{
	int i;

	for(i = -1; i < 13; i++)
	{
		printf("The name of %d transfer function is: %s\n", i, ann_get_transfer_func_name(i));
	}

	return 0;
}
