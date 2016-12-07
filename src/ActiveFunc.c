#include <math.h>

#include "ActiveFunc.h"

char *aFuncMsg[AFUNC_RESERVED] = 
{
    "Sigmoidal",
    "Hyperbolic Tangent",
    "ArcTangent",
    "SoftSign",
    "Gaussian",
    "Diagonal"
};

double (*aFuncBox[AFUNC_RESERVED])(double) = 
{
    AFUNC_Sigmoidal,
    AFUNC_Tanh,
    AFUNC_arcTan,
    AFUNC_Softsign,
    AFUNC_Gaussian,
    AFUNC_Diagonal
};

double (*aFuncBox_Derivative[AFUNC_RESERVED])(double) = 
{
    AFUNC_Sigmoidal_Derivative,
    AFUNC_Tanh_Derivative,
    AFUNC_arcTan_Derivative,
    AFUNC_Softsign_Derivative,
    AFUNC_Gaussian_Derivative,
    AFUNC_Diagonal_Derivative
};

double AFUNC_Sigmoidal(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

double AFUNC_Sigmoidal_Derivative(double x)
{
    return AFUNC_Sigmoidal(x) * (1.0 - AFUNC_Sigmoidal(x));
}

double AFUNC_Tanh(double x)
{
    return 2.0 / (1.0 + exp(-2.0 * x)) - 1.0;
}

double AFUNC_Tanh_Derivative(double x)
{
    return 1.0 - AFUNC_Tanh(x) * AFUNC_Tanh(x);
}

double AFUNC_arcTan(double x)
{
    return atan(x);
}

double AFUNC_arcTan_Derivative(double x)
{
    return 1.0 / (pow(x, 2) + 1.0);
}


double AFUNC_Softsign(double x)
{
    return x / (1.0 + fabs(x));
}

double AFUNC_Softsign_Derivative(double x)
{
    return 1.0 / pow((1.0 + fabs(x)), 2);
}

double AFUNC_Gaussian(double x)
{
    return exp(-pow(x, 2));
}

double AFUNC_Gaussian_Derivative(double x)
{
    return -2.0 * x * exp(-pow(x, 2));
}

double AFUNC_Diagonal(double x)
{
    return x;
}

double AFUNC_Diagonal_Derivative(double x)
{
    return 1.0;
}