#include <math.h>

int MLIB_Transpose(double** matOut, double** matIn, int inRows, int inCols)
{
    int i, j;
    
    for(i = 0; i < inCols; i++)
    {
        for(j = 0; j < inRows; j++)
        {
            matOut[i][j] = matIn[j][i];
        }
    }
    
    return 0;
}

double MLIB_FindMSE_Derivative(double* desireOutput, double* realOutput, int arrayLen)
{
    int i;
    double result;
    
    result = 0;
    for(i = 0; i < arrayLen; i++)
    {
        result += desireOutput[i] - realOutput[i];
    }
    result /= (double)arrayLen;
    
    return result;
}

double MLIB_FindRMSE(double* desireOutput, double* realOutput, int arrayLen)
{
    int i;
    double result;
    
    result = 0;
    for(i = 0; i < arrayLen; i++)
    {
        result += pow((desireOutput[i] - realOutput[i]), 2);
    }
    result /= (double)arrayLen;
    
    result = sqrt(result);
    
    return result;
}

double MLIB_FindMSE(double* desireOutput, double* realOutput, int arrayLen)
{
    int i;
    double result;
    
    result = 0;
    for(i = 0; i < arrayLen; i++)
    {
        result += pow((desireOutput[i] - realOutput[i]), 2);
    }
    result /= (double)arrayLen;
    
    return result;
}

double MLIB_FindNMSE(double* desireOutput, double* realOutput, int arrayLen)
{
    int i;
    double calcTmp1, calcTmp2;
    double result;
    
    result = 0;
    calcTmp1 = 0;
    calcTmp2 = 0;
    for(i = 0; i < arrayLen; i++)
    {
        result += pow((desireOutput[i] - realOutput[i]), 2);
        calcTmp1 += desireOutput[i];
        calcTmp2 += realOutput[i];
    }
    
    calcTmp1 /= (double)arrayLen;
    calcTmp2 /= (double)arrayLen;
    result /= (double)arrayLen;
    result /= (calcTmp1 * calcTmp2);
    
    return result;
}