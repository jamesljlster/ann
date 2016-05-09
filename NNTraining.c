#include <stdio.h>
#include <stdlib.h>

#include "NNLIB.h"

double NNTraining (double* nodeData, double* weight, int dataCount)
{
    int count = 0;
    double output = 0.0;
    for (count = 0; count < dataCount; count++){
        output = output + nodeData[count]*weight[count];
    }
//    output = output * ActivationFunction();
    return output;
}
