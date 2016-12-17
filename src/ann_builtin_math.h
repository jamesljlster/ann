#ifndef __ANN_BUILTIN_MATH_H__
#define __ANN_BUILTIN_MATH_H__

extern double (*ann_transfer_list[])(double);
extern double (*ann_transfer_derivative_list[])(double);
extern char* ann_transfer_func_name[];

#ifdef __cplusplus
extern "C" {
#endif

int ann_get_transfer_func_id(char* str);

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

#ifdef __cplusplus
}
#endif

#endif
