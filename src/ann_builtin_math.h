#ifndef __ANN_BUILTIN_MATH_H__
#define __ANN_BUILTIN_MATH_H__

// Ann transfer function private definition
#define ANN_TFUNC_AMOUNT 12
#define ANN_TFUNC_RESERVED 14  // Reserve for parsing ann model file

extern float (*ann_transfer_list[])(float);
extern float (*ann_transfer_derivative_list[])(float);
extern char* ann_transfer_func_name[];

#ifdef __cplusplus
extern "C"
{
#endif

    float ann_sigmoid(float x);
    float ann_sigmoid_derivative(float x);

    float ann_modified_sigmoid(float x);
    float ann_modified_sigmoid_derivative(float x);

    float ann_tanh(float x);
    float ann_tanh_derivative(float x);

    float ann_gaussian(float x);
    float ann_gaussian_derivative(float x);

    float ann_modified_gaussian(float x);
    float ann_modified_gaussian_derivative(float x);

    float ann_bent_identity(float x);
    float ann_bent_identity_derivative(float x);

    float ann_softplus(float x);
    float ann_softplus_derivative(float x);

    float ann_softsign(float x);
    float ann_softsign_derivative(float x);

    float ann_sinc(float x);
    float ann_sinc_derivative(float x);

    float ann_sinusoid(float x);
    float ann_sinusoid_derivative(float x);

    float ann_identity(float x);
    float ann_identity_derivative(float x);

    float ann_relu(float x);
    float ann_relu_derivative(float x);

#ifdef __cplusplus
}
#endif

#endif
