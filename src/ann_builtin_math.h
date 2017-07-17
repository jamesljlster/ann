#ifndef __ANN_BUILTIN_MATH_H__
#define __ANN_BUILTIN_MATH_H__

enum ANN_TFUNC_PRIVDEF	// Ann transfer function private definition
{
	ANN_TFUNC_AMOUNT	= 12,
	ANN_TFUNC_MULTIPLE,
	ANN_TFUNC_CUSTOM
};

extern double (*ann_transfer_list[])(double);
extern double (*ann_transfer_derivative_list[])(double);
extern char* ann_transfer_func_name[];

#ifdef __cplusplus
extern "C" {
#endif

double ann_sigmoid(double x);
double ann_sigmoid_derivative(double x);

double ann_modified_sigmoid(double x);
double ann_modified_sigmoid_derivative(double x);

double ann_tanh(double x);
double ann_tanh_derivative(double x);

double ann_gaussian(double x);
double ann_gaussian_derivative(double x);

double ann_modified_gaussian(double x);
double ann_modified_gaussian_derivative(double x);

double ann_bent_identity(double x);
double ann_bent_identity_derivative(double x);

double ann_softplus(double x);
double ann_softplus_derivative(double x);

double ann_softsign(double x);
double ann_softsign_derivative(double x);

double ann_sinc(double x);
double ann_sinc_derivative(double x);

double ann_sinusoid(double x);
double ann_sinusoid_derivative(double x);

double ann_identity(double x);
double ann_identity_derivative(double x);

double ann_relu(double x);
double ann_relu_derivative(double x);

#ifdef __cplusplus
}
#endif

#endif
