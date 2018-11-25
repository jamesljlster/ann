#include <math.h>

#include "ann.h"
#include "ann_builtin_math.h"
#include "ann_file_proc.h"

#include "debug.h"

float (*ann_transfer_list[])(float) = {
    ann_sigmoid,            //
    ann_modified_sigmoid,   //
    ann_tanh,               //
    ann_gaussian,           //
    ann_modified_gaussian,  //
    ann_bent_identity,      //
    ann_softplus,           //
    ann_softsign,           //
    ann_sinc,               //
    ann_sinusoid,           //
    ann_identity,           //
    ann_relu                //
};

float (*ann_transfer_derivative_list[])(float) = {
    ann_sigmoid_derivative,            //
    ann_modified_sigmoid_derivative,   //
    ann_tanh_derivative,               //
    ann_gaussian_derivative,           //
    ann_modified_gaussian_derivative,  //
    ann_bent_identity_derivative,      //
    ann_softplus_derivative,           //
    ann_softsign_derivative,           //
    ann_sinc_derivative,               //
    ann_sinusoid_derivative,           //
    ann_identity_derivative,           //
    ann_relu_derivative                //
};

char* ann_transfer_func_name[] = {
    "Sigmoid",                //
    "Mod. Sigmoid",           //
    "Hyperbolic tangent",     //
    "Gaussian",               //
    "Mod. Gaussian",          //
    "Bent Identity",          //
    "SoftPlus",               //
    "SoftSign",               //
    "Sinc",                   //
    "Sinusoid",               //
    "Identity",               //
    "Rectifier Linear Unit",  //
    "Multiple",               // Reserve for ANN_TFUNC_MULTIPLE
    "Custom"                  // Reserve for ANN_TFUNC_CUSTOM
};

int ann_get_transfer_func_id(const char* tFuncName)
{
    int i;
    int iResult;
    int retValue = ANN_INFO_NOT_FOUND;

    LOG("enter");

    // for(i = 0; i < ANN_TFUNC_AMOUNT; i++)
    for (i = 0; i < ANN_TFUNC_RESERVED; i++)
    {
        iResult = ann_strcmp((char*)tFuncName, ann_transfer_func_name[i]);
        if (iResult == ANN_NO_ERROR)
        {
            retValue = i;
            break;
        }
    }

    LOG("exit");

    return retValue;
}

float ann_sigmoid(float x) { return 1.0 / (1.0 + exp(-x)); }

float ann_sigmoid_derivative(float x)
{
    return ann_sigmoid(x) * (1.0 - ann_sigmoid(x));
}

float ann_modified_sigmoid(float x) { return 2.0 * ann_sigmoid(x) - 1.0; }

float ann_modified_sigmoid_derivative(float x)
{
    return 2.0 * ann_sigmoid_derivative(x);
}

float ann_tanh(float x) { return 2.0 / (1.0 + exp(-2.0 * x)) - 1.0; }

float ann_tanh_derivative(float x) { return 1.0 - ann_tanh(x) * ann_tanh(x); }

float ann_gaussian(float x) { return exp(-pow(x, 2) * 0.5); }

float ann_gaussian_derivative(float x) { return -x * exp(-pow(x, 2) * 0.5); }

float ann_modified_gaussian(float x)
{
    if (x == 0)
    {
        return 1;
    }
    else
    {
        return sin(x) / x;
    }
}

float ann_modified_gaussian_derivative(float x)
{
    if (x == 0)
    {
        return 0;
    }
    else
    {
        return (cos(x) / x) - (sin(x) / pow(x, 2));
    }
}

float ann_bent_identity(float x)
{
    return (sqrt(pow(x, 2) + 1.0) - 1) / 2.0 + x;
}

float ann_bent_identity_derivative(float x)
{
    return x / (2.0 * sqrt(pow(x, 2) + 1)) + 1;
}

float ann_softplus(float x) { return log(1.0 + exp(x)); }

float ann_softplus_derivative(float x) { return 1.0 / (1.0 + exp(-x)); }

float ann_softsign(float x) { return x / (1 + fabs(x)); }

float ann_softsign_derivative(float x) { return 1.0 / pow(1.0 + fabs(x), 2); }

float ann_sinc(float x)
{
    if (x == 0.0)
    {
        return 1.0;
    }
    else
    {
        return sin(x) / x;
    }
}

float ann_sinc_derivative(float x)
{
    if (x == 0.0)
    {
        return 0.0;
    }
    else
    {
        return (cos(x) / x) - (sin(x) / pow(x, 2));
    }
}

float ann_sinusoid(float x) { return sin(x); }

float ann_sinusoid_derivative(float x) { return cos(x); }

float ann_identity(float x) { return x; }

float ann_identity_derivative(float x) { return 1; }

float ann_relu(float x)
{
    if (x < 0.0)
    {
        return 0;
    }
    else
    {
        return x;
    }
}

float ann_relu_derivative(float x)
{
    if (x < 0.0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
