/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 * C source code generated on: Thu Oct 11 23:26:05 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ricianDenoiseTiled.h"
#include "rdivide.h"
#include "ricianDenoiseTiled_emxutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void rdivide(const emxArray_real_T *x, const emxArray_real_T *y, emxArray_real_T
             *z)
{
  int32_T i9;
  int32_T loop_ub;
  i9 = z->sizeX[0] * z->sizeX[1];
  z->sizeX[0] = x->sizeX[0];
  z->sizeX[1] = x->sizeX[1];
  emxEnsureCapacity((emxArray__common *)z, i9, (int32_T)sizeof(real_T));
  loop_ub = x->sizeX[0] * x->sizeX[1] - 1;
  for (i9 = 0; i9 <= loop_ub; i9++) {
    z->data[i9] = x->data[i9] / y->data[i9];
  }
}

/* End of code generation (rdivide.c) */
