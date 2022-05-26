/*
 * interpolation.c
 *
 *  Created on: May 26, 2022
 *      Author: hugoA
 */
#include "interpolation.h"

float lookup_table2D_interpolation(float x, float y, float X[], int SIZE_X, float Y[], int SIZE_Y, float* Z)
{
// Compute the bilinear interpolation for a 2D lookup table

  int ix1,ix2;
  int iy1,iy2;
  indices(x, X, SIZE_X, &ix1, &ix2);
  indices(y, Y, SIZE_Y, &iy1, &iy2);

  //Z[x][y] = Z[SIZE_Y*x+y];

  float z = bilinear_interpolation(x, y, X[ix1], X[ix2], Y[iy1], Y[iy2], Z[SIZE_Y*ix1 + iy1], Z[SIZE_Y*ix1 + iy2], Z[SIZE_Y*ix2 + iy1], Z[SIZE_Y*ix2 + iy2]);

  return(z);
}

float bilinear_interpolation(float x, float y, float x1, float x2, float y1, float y2, float z11, float z12, float z21, float z22)
{
	float dx1 = x-x1;
	float dx2 = x2-x;
	float dy1 = y-y1;
	float dy2 = y2-y;
	float dxdy = (x2-x1)*(y2-y1);

	float z = dy2*dx2*z11 + dy2*dx1*z12 + dy1*dx2*z21 + dy1*dx1*z22;
	z = z/dxdy;
	return(z);
}

void indices(float x, float L[], int SIZE_L, int* ia, int* ib)
{
//return indices of the value under & over x in the increasing order list L
  if (x >= L[SIZE_L-1])
  {
    *ia = SIZE_L-1;
    *ib = SIZE_L;
  }
  else
  {
    for (int i=1; i<SIZE_L; i++)
    {
      if (x < L[i])
      {
        *ia = i-1;
        *ib = i;
        break;
      }
    }
  }
}
