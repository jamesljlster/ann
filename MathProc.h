#ifndef MATHPROC_H_INCLUDED
#define MATHPROC_H_INCLUDED

int MLIB_Transpose(double** matOut, double** matIn, int inRows, int inCols);

double MLIB_FindMSE_Derivative(double* desireOutput, double* realOutput, int arrayLen);
double MLIB_FindMSE(double* desireOutput, double* realOutput, int arrayLen);
double MLIB_FindNMSE(double* desireOutput, double* realOutput, int arrayLen);
double MLIB_FindRMSE(double* desireOutput, double* realOutput, int arrayLen);

#endif