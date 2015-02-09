/*
 * ricianDenoiseTiled_emxAPI.c
 *
 * Code generation for function 'ricianDenoiseTiled_emxAPI'
 *
 * C source code generated on: Thu Oct 11 23:26:05 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ricianDenoiseTiled.h"
#include "ricianDenoiseTiled_emxAPI.h"
#include "ricianDenoiseTiled_emxutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
emxArray_real_T *emxCreateND_real_T(int32_T numDimensions, int32_T *sizeX)
{
  emxArray_real_T *emx;
  int32_T numEl;
  int32_T loop_ub;
  int32_T i;
  c_emxInit_real_T(&emx, numDimensions);
  numEl = 1;
  loop_ub = numDimensions - 1;
  for (i = 0; i <= loop_ub; i++) {
    numEl *= sizeX[i];
    emx->sizeX[i] = sizeX[i];
  }

  emx->data = (real_T *)hc_malloc((uint32_T)numEl * sizeof(real_T));
  memset(emx->data, 0, (uint32_T)numEl * sizeof(real_T));
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  return emx;
}

emxArray_real_T *emxCreateWrapperND_real_T(real_T *data, int32_T numDimensions,
  int32_T *sizeX)
{
  emxArray_real_T *emx;
  int32_T numEl;
  int32_T loop_ub;
  int32_T i;
  c_emxInit_real_T(&emx, numDimensions);
  numEl = 1;
  loop_ub = numDimensions - 1;
  for (i = 0; i <= loop_ub; i++) {
    numEl *= sizeX[i];
    emx->sizeX[i] = sizeX[i];
  }

  emx->data = data;
  emx->numDimensions = numDimensions;
  emx->allocatedSize = numEl;
  emx->canFreeData = FALSE;
  return emx;
}

emxArray_real_T *emxCreateWrapper_real_T(real_T *data, int32_T rows, int32_T
  cols)
{
  emxArray_real_T *emx;
  int32_T sizeX[2];
  int32_T numEl;
  int32_T i;
  sizeX[0] = rows;
  sizeX[1] = cols;
  c_emxInit_real_T(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= sizeX[i];
    emx->sizeX[i] = sizeX[i];
  }

  emx->data = data;
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  emx->canFreeData = FALSE;
  return emx;
}

emxArray_real_T *emxCreate_real_T(int32_T rows, int32_T cols)
{
  emxArray_real_T *emx;
  int32_T sizeX[2];
  int32_T numEl;
  int32_T i;
  sizeX[0] = rows;
  sizeX[1] = cols;
  c_emxInit_real_T(&emx, 2);
  numEl = 1;
  for (i = 0; i < 2; i++) {
    numEl *= sizeX[i];
    emx->sizeX[i] = sizeX[i];
  }

  emx->data = (real_T *)hc_malloc((uint32_T)numEl * sizeof(real_T));
  memset(emx->data, 0, (uint32_T)numEl * sizeof(real_T));
  emx->numDimensions = 2;
  emx->allocatedSize = numEl;
  return emx;
}

void emxDestroyArray_real_T(emxArray_real_T *emxArray)
{
  emxFree_real_T(&emxArray);
}

/* End of code generation (ricianDenoiseTiled_emxAPI.c) */
