#ifndef ACTIVFUNC_H_INCLUDED
#define ACTIVFUNC_H_INCLUDED

enum AFUNC_INDEX
{
    AFUNC_SIGMOIDAL,
    AFUNC_TANH,
    AFUNC_ARCTAN,
    AFUNC_SOFTSIGN,
    AFUNC_GAUSSIAN,
    AFUNC_DIAGONAL,
    
    AFUNC_RESERVED
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern char *aFuncMsg[];
extern double (*aFuncBox[])(double);
extern double (*aFuncBox_Derivative[])(double);

extern double AFUNC_Sigmoidal(double x);
extern double AFUNC_Sigmoidal_Derivative(double x);

extern double AFUNC_Tanh(double x);
extern double AFUNC_Tanh_Derivative(double x);

extern double AFUNC_arcTan(double x);
extern double AFUNC_arcTan_Derivative(double x);

extern double AFUNC_Softsign(double x);
extern double AFUNC_Softsign_Derivative(double x);

extern double AFUNC_Gaussian(double x);
extern double AFUNC_Gaussian_Derivative(double x);

extern double AFUNC_Diagonal(double x);
extern double AFUNC_Diagonal_Derivative(double x);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif