#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <ann_private.h>

int main()
{
	srand(time(NULL));

	while(1)
	{
		printf("%+lf\n", ann_rand());
	}

	return 0;
}
