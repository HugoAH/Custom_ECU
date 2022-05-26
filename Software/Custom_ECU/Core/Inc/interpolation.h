/*
 * interpolation.h
 *
 *  Created on: May 26, 2022
 *      Author: hugoA
 */

#ifndef INC_INTERPOLATION_H_
#define INC_INTERPOLATION_H_

float lookup_table2D_interpolation(float x, float y, float X[], int SIZE_X, float Y[], int SIZE_Y, float* Z);
float bilinear_interpolation(float x, float y, float x1, float x2, float y1, float y2, float z11, float z12, float z21, float z22);
void indices(float x, float* L, int N, int* a, int* b);

#endif /* INC_INTERPOLATION_H_ */
