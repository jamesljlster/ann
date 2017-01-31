#include <math.h>

#include "ann.h"
#include "ann_file_proc.h"
#include "ann_builtin_math.h"

#include "debug.h"

double (*ann_transfer_list[])(double) = {
	ann_sigmoid,
	ann_modified_sigmoid,
	ann_tanh,
	ann_gaussian,
	ann_modified_gaussian
};

double (*ann_transfer_derivative_list[])(double) = {
	ann_sigmoid_derivative,
	ann_modified_sigmoid_derivative,
	ann_tanh_derivative,
	ann_gaussian_derivative,
	ann_modified_gaussian_derivative
};

char* ann_transfer_func_name[] = {
	"Sigmoid",
	"Mod. Sigmoid",
	"Hyperbolic tangent",
	"Gaussian",
	"Mod. Gaussian"
};

int ann_get_transfer_func_id(char* str)
{
	int i;
	int iResult;
	int retValue = ANN_INFO_NOT_FOUND;

	log("enter");

	for(i = 0; i < 5; i++)
	{
		iResult = ann_strcmp(str, ann_transfer_func_name[i]);
		if(iResult == ANN_NO_ERROR)
		{
			retValue = i;
			break;
		}
	}

	log("exit");

	return retValue;
}

double ann_sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

double ann_sigmoid_derivative(double x)
{
    return ann_sigmoid(x) * (1.0 - ann_sigmoid(x));
}

double ann_modified_sigmoid(double x)
{
	return 2.0 * ann_sigmoid(x) - 1.0;
}

double ann_modified_sigmoid_derivative(double x)
{
	return 2.0 * ann_sigmoid_derivative(x);
}

double ann_tanh(double x)
{
    return 2.0 / (1.0 + exp(-2.0 * x)) - 1.0;
}

double ann_tanh_derivative(double x)
{
    return 1.0 - ann_tanh(x) * ann_tanh(x);
}

double ann_gaussian(double x)
{
    return exp(-pow(x, 2) * 0.5);
}

double ann_gaussian_derivative(double x)
{
    return -2.0 * x * exp(-pow(x, 2) + 0.5);
}

double ann_modified_gaussian(double x)
{
	return x;
}

double ann_modified_gaussian_derivative(double x)
{
	return x;
}


