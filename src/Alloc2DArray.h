/**
 *  @author     ZHENG-LING LAI <jamesjlster@gmail.com>
 *  @file       Alloc2DArray.h
 *  @copyright  Copyright (C) 2015 ZHENG-LING LAI (James Lai). All Rights Reserved.
**/

#ifndef ALLOC2DARRAY_H_INCLUDED
#define ALLOC2DARRAY_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern void* Alloc2DArray(int rows, int cols, size_t sizeOfElement);
/**
 *  @fn     void* Alloc2DArray(int rows, int cols, size_t sizeOfElement)
 *  @brief  Allocate memory for a 3D array of size rows * cols * depth.
 *  @param  rows:           Rows, length of x-axis.
 *  @param  cols:           Columns, length of y-axis.
 *  @param  sizeOfElement:  Size in bytes of the array element.
 *  @return If allocate memory successfully, it would return a universal pointer, or NULL would be returned.
 */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ALLOC2DARRAY_H_INCLUDED

/**
 *  @mainpage   Allocate Memory for 2D Array
 *  The function is used to allocate memory for 2D array of any types.
 *  The way to use the function is similar with calloc().
 *
 *  Example:
 *  To allocate a 3 x 4 2D array of double type, you should declare a two-level pointer of double type first.
 *
 *      double** array;
 *
 *  Then, call Alloc2DArray().
 *
 *      array = (double**)Alloc2DArryay(3, 4, sizeof(double));
 *
 *  To free the memory allocated with the function, just call free().
 *
 *      free(array);
**/
