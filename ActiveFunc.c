#include <math.h>

double activeFunc_Sigmoidal(double input)
{
    return 1.0 / (1.0 + exp(-input));
}

double dActiveFunc_Sigmoidal(double input)
{
    return activeFunc_Sigmoidal(input) * (1 - activeFunc_Sigmoidal(input));
}