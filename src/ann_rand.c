#include <stdlib.h>
#include <time.h>

#define NUM_PRECISION	1000000
#define NUM_MAX			1
#define	NUM_MIN			-1

double ann_rand()
{
	int randRange;

	randRange = (NUM_MAX - NUM_MIN) * NUM_PRECISION + 1;

	return (double)(rand() % randRange) / (double)(NUM_PRECISION) + (double)NUM_MIN;
}
