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
	ann_modified_gaussian,
	ann_bent_identity,
	ann_softplus,
	ann_softsign,
	ann_sinc,
	ann_sinusoid,
	ann_identity,
	ann_relu
};

double (*ann_transfer_derivative_list[])(double) = {
	ann_sigmoid_derivative,
	ann_modified_sigmoid_derivative,
	ann_tanh_derivative,
	ann_gaussian_derivative,
	ann_modified_gaussian_derivative,
	ann_bent_identity_derivative,
	ann_softplus_derivative,
	ann_softsign_derivative,
	ann_sinc_derivative,
	ann_sinusoid_derivative,
	ann_identity_derivative,
	ann_relu_derivative
};

char* ann_transfer_func_name[] = {
	"Sigmoid",
	"Mod. Sigmoid",
	"Hyperbolic tangent",
	"Gaussian",
	"Mod. Gaussian",
	"Bent Identity",
	"SoftPlus",
	"SoftSign",
	"Sinc",
	"Sinusoid",
	"Identity",
	"Rectifier Linear Unit",
	"Multiple",					// Reserve for ANN_TFUNC_MULTIPLE
	"Custom"					// Reserve for ANN_TFUNC_CUSTOM
};

int ann_get_transfer_func_id(const char* tFuncName)
{
	int i;
	int iResult;
	int retValue = ANN_INFO_NOT_FOUND;

	LOG("enter");

	//for(i = 0; i < ANN_TFUNC_AMOUNT; i++)
	for(i = 0; i < ANN_TFUNC_RESERVED; i++)
	{
		iResult = ann_strcmp((char*)tFuncName, ann_transfer_func_name[i]);
		if(iResult == ANN_NO_ERROR)
		{
			retValue = i;
			break;
		}
	}

	LOG("exit");

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
    return -x * exp(-pow(x, 2) * 0.5);
}

double ann_modified_gaussian(double x)
{
	if(x == 0)
	{
		return 1;
	}
	else
	{
		return sin(x) / x;
	}
}

double ann_modified_gaussian_derivative(double x)
{
	if(x == 0)
	{
		return 0;
	}
	else
	{
		return (cos(x) / x) - (sin(x) / pow(x, 2));
	}
}

double ann_bent_identity(double x)
{
	return (sqrt(pow(x, 2) + 1.0) - 1) / 2.0 + x;
}

double ann_bent_identity_derivative(double x)
{
	return x / (2.0 * sqrt(pow(x, 2) + 1)) + 1;
}

double ann_softplus(double x)
{
	return log(1.0 + exp(x));
}

double ann_softplus_derivative(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

double ann_softsign(double x)
{
	return x / (1 + fabs(x));
}

double ann_softsign_derivative(double x)
{
	return 1.0 / pow(1.0 + fabs(x), 2);
}

double ann_sinc(double x)
{
	if(x == 0.0)
	{
		return 1.0;
	}
	else
	{
		return sin(x) / x;
	}
}

double ann_sinc_derivative(double x)
{
	if(x == 0.0)
	{
		return 0.0;
	}
	else
	{
		return (cos(x) / x) - (sin(x) / pow(x, 2));
	}
}

double ann_sinusoid(double x)
{
	return sin(x);
}

double ann_sinusoid_derivative(double x)
{
	return cos(x);
}

double ann_identity(double x)
{
	return x;
}

double ann_identity_derivative(double x)
{
	return 1;
}

double ann_relu(double x)
{
	if(x < 0.0)
	{
		return 0;
	}
	else
	{
		return x;
	}
}

double ann_relu_derivative(double x)
{
	if(x < 0.0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

