#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ann_builtin_math.h>

#define MAX		5.0
#define MIN		-5.0
#define STEP	1.0
#define DX_EXP	-5

int main()
{
	int i;
	int counter;
	double x;
	double dx;
	double error;
	double derivative;

	dx = pow(10, DX_EXP);
	assert(dx > 0);

	for(i = 0; i < 5; i++)
	{
		printf("Test %s derivative...\n", ann_transfer_func_name[i]);

		error = 0;
		x = MIN;
		while(x <= MAX)
		{
			derivative = (ann_transfer_list[i](x + dx) - ann_transfer_list[i](x)) / dx;
			error += derivative - ann_transfer_derivative_list[i](x);
			printf("Limitation: %lf, Derivative: %lf\n", derivative, ann_transfer_derivative_list[i](x));

			x += STEP;
		}

		printf("Sum Error: %lf\n\n", error);
	}
			
	return 0;
}
