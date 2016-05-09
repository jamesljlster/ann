/**
 *  Author: ZHENG-LING LAI <jamesljlster@gmail.com>
 *  File:   Alloc2DArray.c
 *
 *  Copyright (C) 2015 ZHENG-LING LAI (James Lai). All Rights Reserved.
**/

#include <stdlib.h>
#include <string.h>

#define UNIT_TYPE char

// Function: Allocate 2-Dimension Array
void* Alloc2DArray(int rows, int cols, size_t sizeOfElement)
{
    int i;

    UNIT_TYPE** memPtr = NULL;
    UNIT_TYPE* tmpPtr = NULL;

    // Allocate a continuous memory space for 2D array.
    memPtr = (UNIT_TYPE**)malloc(rows * sizeof(UNIT_TYPE*) + rows * cols * sizeOfElement);
    if(memPtr == NULL)
    {
        return NULL;
    }

    // Setting 1D array pointer under the current 2D array.
    tmpPtr = (UNIT_TYPE*)memPtr + rows * sizeof(UNIT_TYPE*);
    for(i=0; i<rows; i++)
    {
        memPtr[i] = tmpPtr + (i * cols * sizeOfElement);
    }

    // Initial content of the current 2D array to zero.
    memset(tmpPtr, 0, rows * cols * sizeOfElement);

    return (void*)memPtr;
}
