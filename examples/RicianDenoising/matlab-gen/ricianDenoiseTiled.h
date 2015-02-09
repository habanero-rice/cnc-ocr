/*
 * ricianDenoiseTiled.h
 *
 * Code generation for function 'ricianDenoiseTiled'
 *
 * C source code generated on: Thu Oct 11 23:26:05 2012
 *
 */

#ifndef __RICIANDENOISETILED_H__
#define __RICIANDENOISETILED_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "hc.h"

#include "rtwtypes.h"
#include "ricianDenoiseTiled_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
#ifdef __cplusplus
extern "C" {
#endif
extern void ricianDenoiseTiled(const emxArray_real_T *imageTiled, real_T blockSize, real_T sigma, real_T lambda, emxArray_real_T *u);

extern void gStep(real_T blockSize, const emxArray_real_T *u_ij, const
                  emxArray_real_T *ut_ij, const emxArray_real_T *ur_ij, const
                  emxArray_real_T *ud_ij, const emxArray_real_T *ul_ij,
                  emxArray_real_T *g);
extern void rStep(real_T blockSize, const emxArray_real_T *u_ij, const
                  emxArray_real_T *img_ij, real_T sigma2, emxArray_real_T *r);

extern real_T rt_roundd_snf(real_T u);

extern void uDiffStep(real_T i, real_T j, real_T blockSize, real_T tileRows,
                      real_T tileCols, const emxArray_real_T *ulast_cur, const
                      emxArray_real_T *ulast_top, const emxArray_real_T
                      *ulast_rig, const emxArray_real_T *ulast_dow, const
                      emxArray_real_T *ulast_lef, emxArray_real_T *ut,
                      emxArray_real_T *ur, emxArray_real_T *ud, emxArray_real_T *
                      ul);


extern void ugStep(real_T blockSize, const emxArray_real_T *u_ij, const
                      emxArray_real_T *g_ij, emxArray_real_T *ug);

extern void uStep(real_T i, real_T j, real_T blockSize, real_T tileRows, real_T
                  tileCols, const emxArray_real_T *ug_cur, const emxArray_real_T
                  *ug_top, const emxArray_real_T *ug_rig, const emxArray_real_T *
                  ug_dow, const emxArray_real_T *ug_lef, const emxArray_real_T
                  *gt, const emxArray_real_T *gr, const emxArray_real_T *gd,
                  const emxArray_real_T *gl, const emxArray_real_T *u_ij, const
                  emxArray_real_T *img_ij, const emxArray_real_T *r_ij, real_T
                  b_gamma, emxArray_real_T *u);

#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (ricianDenoiseTiled.h) */
