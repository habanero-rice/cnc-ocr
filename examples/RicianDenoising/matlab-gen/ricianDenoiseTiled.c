/*
 * ricianDenoiseTiled.c
 *
 * Code generation for function 'ricianDenoiseTiled'
 *
 * C source code generated on: Tue Oct 16 20:09:47 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ricianDenoiseTiled.h"
#include "ricianDenoiseTiled_emxutil.h"
#include "rdivide.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void gStep(real_T blockSize, const emxArray_real_T *u_ij, const
                  emxArray_real_T *ut_ij, const emxArray_real_T *ur_ij, const
                  emxArray_real_T *ud_ij, const emxArray_real_T *ul_ij,
                  emxArray_real_T *g)
{
  int32_T b_g;
  int32_T loop_ub;
  emxArray_real_T *eur;
  emxArray_real_T *eud;
  emxArray_real_T *eul;
  b_g = g->sizeX[0] * g->sizeX[1];
  g->sizeX[0] = ut_ij->sizeX[0];
  g->sizeX[1] = ut_ij->sizeX[1];
  emxEnsureCapacity((emxArray__common *)g, b_g, (int32_T)sizeof(real_T));
  loop_ub = ut_ij->sizeX[0] * ut_ij->sizeX[1] - 1;
  for (b_g = 0; b_g <= loop_ub; b_g++) {
    g->data[b_g] = ut_ij->data[b_g] - u_ij->data[b_g];
  }

  b_emxInit_real_T(&eur, 2);
  b_g = eur->sizeX[0] * eur->sizeX[1];
  eur->sizeX[0] = ur_ij->sizeX[0];
  eur->sizeX[1] = ur_ij->sizeX[1];
  emxEnsureCapacity((emxArray__common *)eur, b_g, (int32_T)sizeof(real_T));
  loop_ub = ur_ij->sizeX[0] * ur_ij->sizeX[1] - 1;
  for (b_g = 0; b_g <= loop_ub; b_g++) {
    eur->data[b_g] = ur_ij->data[b_g] - u_ij->data[b_g];
  }

  b_emxInit_real_T(&eud, 2);
  b_g = eud->sizeX[0] * eud->sizeX[1];
  eud->sizeX[0] = ud_ij->sizeX[0];
  eud->sizeX[1] = ud_ij->sizeX[1];
  emxEnsureCapacity((emxArray__common *)eud, b_g, (int32_T)sizeof(real_T));
  loop_ub = ud_ij->sizeX[0] * ud_ij->sizeX[1] - 1;
  for (b_g = 0; b_g <= loop_ub; b_g++) {
    eud->data[b_g] = ud_ij->data[b_g] - u_ij->data[b_g];
  }

  b_emxInit_real_T(&eul, 2);
  b_g = eul->sizeX[0] * eul->sizeX[1];
  eul->sizeX[0] = ul_ij->sizeX[0];
  eul->sizeX[1] = ul_ij->sizeX[1];
  emxEnsureCapacity((emxArray__common *)eul, b_g, (int32_T)sizeof(real_T));
  loop_ub = ul_ij->sizeX[0] * ul_ij->sizeX[1] - 1;
  for (b_g = 0; b_g <= loop_ub; b_g++) {
    eul->data[b_g] = ul_ij->data[b_g] - u_ij->data[b_g];
  }

  b_g = g->sizeX[0] * g->sizeX[1];
  g->sizeX[0] = g->sizeX[0];
  g->sizeX[1] = g->sizeX[1];
  emxEnsureCapacity((emxArray__common *)g, b_g, (int32_T)sizeof(real_T));
  loop_ub = g->sizeX[0];
  b_g = g->sizeX[1];
  loop_ub = loop_ub * b_g - 1;
  for (b_g = 0; b_g <= loop_ub; b_g++) {
    g->data[b_g] = (((1.0E-20 + g->data[b_g] * g->data[b_g]) + eur->data[b_g] *
                     eur->data[b_g]) + eud->data[b_g] * eud->data[b_g]) +
      eul->data[b_g] * eul->data[b_g];
  }

  emxFree_real_T(&eul);
  emxFree_real_T(&eud);
  emxFree_real_T(&eur);

  /*  Approximate 1/|grad u| */
  b_g = g->sizeX[0] * g->sizeX[1];
  for (loop_ub = 0; loop_ub <= b_g - 1; loop_ub++) {
    g->data[loop_ub] = sqrt(g->data[loop_ub]);
  }

  b_g = g->sizeX[0] * g->sizeX[1];
  g->sizeX[0] = g->sizeX[0];
  g->sizeX[1] = g->sizeX[1];
  emxEnsureCapacity((emxArray__common *)g, b_g, (int32_T)sizeof(real_T));
  loop_ub = g->sizeX[0];
  b_g = g->sizeX[1];
  loop_ub = loop_ub * b_g - 1;
  for (b_g = 0; b_g <= loop_ub; b_g++) {
    g->data[b_g] = 1.0 / g->data[b_g];
  }
}

void rStep(real_T blockSize, const emxArray_real_T *u_ij, const
                  emxArray_real_T *img_ij, real_T sigma2, emxArray_real_T *r)
{
  emxArray_real_T *r_temp;
  int32_T i8;
  int32_T loop_ub;
  emxArray_real_T *b_r_temp;
  emxArray_real_T *r41;
  b_emxInit_real_T(&r_temp, 2);

  /*  Evaluate I1(inImage.*u/sigma^2) ./ I0(inImage.*u/sigma^2) */
  i8 = r_temp->sizeX[0] * r_temp->sizeX[1];
  r_temp->sizeX[0] = u_ij->sizeX[0];
  r_temp->sizeX[1] = u_ij->sizeX[1];
  emxEnsureCapacity((emxArray__common *)r_temp, i8, (int32_T)sizeof(real_T));
  loop_ub = u_ij->sizeX[0] * u_ij->sizeX[1] - 1;
  for (i8 = 0; i8 <= loop_ub; i8++) {
    r_temp->data[i8] = u_ij->data[i8] * img_ij->data[i8] / sigma2;
  }

  b_emxInit_real_T(&b_r_temp, 2);

  /*  Rational approximation of I1(r)./I0(r): Approximation is L^inf */
  /*  optimal with error less than 8e-4 for all x >= 0. */
  i8 = b_r_temp->sizeX[0] * b_r_temp->sizeX[1];
  b_r_temp->sizeX[0] = r_temp->sizeX[0];
  b_r_temp->sizeX[1] = r_temp->sizeX[1];
  emxEnsureCapacity((emxArray__common *)b_r_temp, i8, (int32_T)sizeof(real_T));
  loop_ub = r_temp->sizeX[0] * r_temp->sizeX[1] - 1;
  for (i8 = 0; i8 <= loop_ub; i8++) {
    b_r_temp->data[i8] = r_temp->data[i8] * (2.38944 + r_temp->data[i8] *
      (0.950037 + r_temp->data[i8]));
  }

  b_emxInit_real_T(&r41, 2);
  i8 = r41->sizeX[0] * r41->sizeX[1];
  r41->sizeX[0] = r_temp->sizeX[0];
  r41->sizeX[1] = r_temp->sizeX[1];
  emxEnsureCapacity((emxArray__common *)r41, i8, (int32_T)sizeof(real_T));
  loop_ub = r_temp->sizeX[0] * r_temp->sizeX[1] - 1;
  for (i8 = 0; i8 <= loop_ub; i8++) {
    r41->data[i8] = 4.65314 + r_temp->data[i8] * (2.57541 + r_temp->data[i8] *
      (1.48937 + r_temp->data[i8]));
  }

  emxFree_real_T(&r_temp);
  rdivide(b_r_temp, r41, r);
  emxFree_real_T(&r41);
  emxFree_real_T(&b_r_temp);
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

void uDiffStep(real_T i, real_T j, real_T blockSize, real_T tileRows,
                      real_T tileCols, const emxArray_real_T *ulast_cur, const
                      emxArray_real_T *ulast_top, const emxArray_real_T
                      *ulast_rig, const emxArray_real_T *ulast_dow, const
                      emxArray_real_T *ulast_lef, emxArray_real_T *ut,
                      emxArray_real_T *ur, emxArray_real_T *ud, emxArray_real_T *
                      ul)
{
  int32_T i3;
  int32_T loop_ub;
  int32_T i4;
  int32_T i5;
  int32_T i6;
  int32_T i7;
  i3 = ut->sizeX[0] * ut->sizeX[1];
  ut->sizeX[0] = (int32_T)blockSize;
  ut->sizeX[1] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ut, i3, (int32_T)sizeof(real_T));
  loop_ub = (int32_T)blockSize * (int32_T)blockSize - 1;
  for (i3 = 0; i3 <= loop_ub; i3++) {
    ut->data[i3] = 0.0;
  }

  i3 = ur->sizeX[0] * ur->sizeX[1];
  ur->sizeX[0] = (int32_T)blockSize;
  ur->sizeX[1] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ur, i3, (int32_T)sizeof(real_T));
  loop_ub = (int32_T)blockSize * (int32_T)blockSize - 1;
  for (i3 = 0; i3 <= loop_ub; i3++) {
    ur->data[i3] = 0.0;
  }

  i3 = ud->sizeX[0] * ud->sizeX[1];
  ud->sizeX[0] = (int32_T)blockSize;
  ud->sizeX[1] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ud, i3, (int32_T)sizeof(real_T));
  loop_ub = (int32_T)blockSize * (int32_T)blockSize - 1;
  for (i3 = 0; i3 <= loop_ub; i3++) {
    ud->data[i3] = 0.0;
  }

  i3 = ul->sizeX[0] * ul->sizeX[1];
  ul->sizeX[0] = (int32_T)blockSize;
  ul->sizeX[1] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ul, i3, (int32_T)sizeof(real_T));
  loop_ub = (int32_T)blockSize * (int32_T)blockSize - 1;
  for (i3 = 0; i3 <= loop_ub; i3++) {
    ul->data[i3] = 0.0;
  }

  if (1.0 > blockSize - 1.0) {
    i3 = -1;
  } else {
    i3 = (int32_T)(blockSize - 1.0) - 1;
  }

  if (2.0 > blockSize) {
    i4 = 0;
  } else {
    i4 = 1;
  }

  i5 = ulast_cur->sizeX[1] - 1;
  for (i6 = 0; i6 <= i5; i6++) {
    for (i7 = 0; i7 <= i3; i7++) {
      ut->data[(i4 + i7) + ut->sizeX[0] * i6] = ulast_cur->data[i7 +
        ulast_cur->sizeX[0] * i6];
    }
  }

  if (i == 1.0) {
    i3 = ulast_cur->sizeX[1] - 1;
    for (i4 = 0; i4 <= i3; i4++) {
      ut->data[ut->sizeX[0] * i4] = ulast_cur->data[ulast_cur->sizeX[0] * i4];
    }
  } else {
    i3 = ulast_top->sizeX[1] - 1;
    for (i4 = 0; i4 <= i3; i4++) {
      ut->data[ut->sizeX[0] * i4] = ulast_top->data[((int32_T)blockSize +
        ulast_top->sizeX[0] * i4) - 1];
    }
  }

  if (1.0 > blockSize - 1.0) {
    i3 = -1;
  } else {
    i3 = (int32_T)(blockSize - 1.0) - 1;
  }

  if (2.0 > blockSize) {
    i4 = 0;
  } else {
    i4 = 1;
  }

  i5 = ulast_cur->sizeX[0] - 1;
  for (i6 = 0; i6 <= i3; i6++) {
    for (i7 = 0; i7 <= i5; i7++) {
      ur->data[i7 + ur->sizeX[0] * (i4 + i6)] = ulast_cur->data[i7 +
        ulast_cur->sizeX[0] * i6];
    }
  }

  if (j == 1.0) {
    i3 = ulast_cur->sizeX[0] - 1;
    for (i4 = 0; i4 <= i3; i4++) {
      ur->data[i4] = ulast_cur->data[i4];
    }
  } else {
    i3 = ulast_rig->sizeX[0] - 1;
    for (i4 = 0; i4 <= i3; i4++) {
      ur->data[i4] = ulast_rig->data[i4 + ulast_rig->sizeX[0] * ((int32_T)
        blockSize - 1)];
    }
  }

  if (2.0 > blockSize) {
    i3 = 0;
    i4 = 0;
  } else {
    i3 = 1;
    i4 = (int32_T)blockSize;
  }

  i5 = ulast_cur->sizeX[1] - 1;
  for (i6 = 0; i6 <= i5; i6++) {
    loop_ub = (i4 - i3) - 1;
    for (i7 = 0; i7 <= loop_ub; i7++) {
      ud->data[i7 + ud->sizeX[0] * i6] = ulast_cur->data[(i3 + i7) +
        ulast_cur->sizeX[0] * i6];
    }
  }

  if (i == tileRows) {
    i3 = ulast_cur->sizeX[1] - 1;
    for (i4 = 0; i4 <= i3; i4++) {
      ud->data[((int32_T)blockSize + ud->sizeX[0] * i4) - 1] = ulast_cur->data
        [((int32_T)blockSize + ulast_cur->sizeX[0] * i4) - 1];
    }
  } else {
    i3 = ulast_dow->sizeX[1] - 1;
    for (i4 = 0; i4 <= i3; i4++) {
      ud->data[((int32_T)blockSize + ud->sizeX[0] * i4) - 1] = ulast_dow->
        data[ulast_dow->sizeX[0] * i4];
    }
  }

  if (2.0 > blockSize) {
    i3 = 0;
    i4 = 0;
  } else {
    i3 = 1;
    i4 = (int32_T)blockSize;
  }

  i5 = ulast_cur->sizeX[0] - 1;
  loop_ub = (i4 - i3) - 1;
  for (i4 = 0; i4 <= loop_ub; i4++) {
    for (i6 = 0; i6 <= i5; i6++) {
      ul->data[i6 + ul->sizeX[0] * i4] = ulast_cur->data[i6 + ulast_cur->sizeX[0] *
        (i3 + i4)];
    }
  }

  if (j == tileCols) {
    i3 = ulast_cur->sizeX[0] - 1;
    for (i4 = 0; i4 <= i3; i4++) {
      ul->data[i4 + ul->sizeX[0] * ((int32_T)blockSize - 1)] = ulast_cur->data[i4
        + ulast_cur->sizeX[0] * ((int32_T)blockSize - 1)];
    }
  } else {
    i3 = ulast_lef->sizeX[0] - 1;
    for (i4 = 0; i4 <= i3; i4++) {
      ul->data[i4 + ul->sizeX[0] * ((int32_T)blockSize - 1)] = ulast_lef->data[i4
        + ulast_lef->sizeX[0] * ((int32_T)blockSize - 1)];
    }
  }
}

void uStep(real_T i, real_T j, real_T blockSize, real_T tileRows, real_T
                  tileCols, const emxArray_real_T *ug_cur, const emxArray_real_T
                  *ug_top, const emxArray_real_T *ug_rig, const emxArray_real_T *
                  ug_dow, const emxArray_real_T *ug_lef, const emxArray_real_T
                  *gt, const emxArray_real_T *gr, const emxArray_real_T *gd,
                  const emxArray_real_T *gl, const emxArray_real_T *u_ij, const
                  emxArray_real_T *img_ij, const emxArray_real_T *r_ij, real_T
                  b_gamma, emxArray_real_T *u)
{
  emxArray_real_T *ugt;
  int32_T i11;
  int32_T loop_ub;
  int32_T i12;
  int32_T i13;
  int32_T i14;
  int32_T i15;
  emxArray_real_T *ugr;
  emxArray_real_T *ugd;
  emxArray_real_T *ugl;
  emxArray_real_T *b_u_ij;
  emxArray_real_T *r42;
  b_emxInit_real_T(&ugt, 2);
  i11 = ugt->sizeX[0] * ugt->sizeX[1];
  ugt->sizeX[0] = (int32_T)blockSize;
  ugt->sizeX[1] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ugt, i11, (int32_T)sizeof(real_T));
  loop_ub = (int32_T)blockSize * (int32_T)blockSize - 1;
  for (i11 = 0; i11 <= loop_ub; i11++) {
    ugt->data[i11] = 0.0;
  }

  if (1.0 > blockSize - 1.0) {
    i11 = -1;
  } else {
    i11 = (int32_T)(blockSize - 1.0) - 1;
  }

  if (2.0 > blockSize) {
    i12 = 0;
  } else {
    i12 = 1;
  }

  i13 = ug_cur->sizeX[1] - 1;
  for (i14 = 0; i14 <= i13; i14++) {
    for (i15 = 0; i15 <= i11; i15++) {
      ugt->data[(i12 + i15) + ugt->sizeX[0] * i14] = ug_cur->data[i15 +
        ug_cur->sizeX[0] * i14];
    }
  }

  if (i == 1.0) {
    i11 = ug_cur->sizeX[1] - 1;
    for (i12 = 0; i12 <= i11; i12++) {
      ugt->data[ugt->sizeX[0] * i12] = ug_cur->data[ug_cur->sizeX[0] * i12];
    }
  } else {
    i11 = ug_top->sizeX[1] - 1;
    for (i12 = 0; i12 <= i11; i12++) {
      ugt->data[ugt->sizeX[0] * i12] = ug_top->data[((int32_T)blockSize +
        ug_top->sizeX[0] * i12) - 1];
    }
  }

  b_emxInit_real_T(&ugr, 2);
  i11 = ugr->sizeX[0] * ugr->sizeX[1];
  ugr->sizeX[0] = (int32_T)blockSize;
  ugr->sizeX[1] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ugr, i11, (int32_T)sizeof(real_T));
  loop_ub = (int32_T)blockSize * (int32_T)blockSize - 1;
  for (i11 = 0; i11 <= loop_ub; i11++) {
    ugr->data[i11] = 0.0;
  }

  if (1.0 > blockSize - 1.0) {
    i11 = -1;
  } else {
    i11 = (int32_T)(blockSize - 1.0) - 1;
  }

  if (2.0 > blockSize) {
    i12 = 0;
  } else {
    i12 = 1;
  }

  i13 = ug_cur->sizeX[0] - 1;
  for (i14 = 0; i14 <= i11; i14++) {
    for (i15 = 0; i15 <= i13; i15++) {
      ugr->data[i15 + ugr->sizeX[0] * (i12 + i14)] = ug_cur->data[i15 +
        ug_cur->sizeX[0] * i14];
    }
  }

  if (j == 1.0) {
    i11 = ug_cur->sizeX[0] - 1;
    for (i12 = 0; i12 <= i11; i12++) {
      ugr->data[i12] = ug_cur->data[i12];
    }
  } else {
    i11 = ug_rig->sizeX[0] - 1;
    for (i12 = 0; i12 <= i11; i12++) {
      ugr->data[i12] = ug_rig->data[i12 + ug_rig->sizeX[0] * ((int32_T)blockSize
        - 1)];
    }
  }

  b_emxInit_real_T(&ugd, 2);
  i11 = ugd->sizeX[0] * ugd->sizeX[1];
  ugd->sizeX[0] = (int32_T)blockSize;
  ugd->sizeX[1] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ugd, i11, (int32_T)sizeof(real_T));
  loop_ub = (int32_T)blockSize * (int32_T)blockSize - 1;
  for (i11 = 0; i11 <= loop_ub; i11++) {
    ugd->data[i11] = 0.0;
  }

  if (2.0 > blockSize) {
    i11 = 0;
    i12 = 0;
  } else {
    i11 = 1;
    i12 = (int32_T)blockSize;
  }

  i13 = ug_cur->sizeX[1] - 1;
  for (i14 = 0; i14 <= i13; i14++) {
    loop_ub = (i12 - i11) - 1;
    for (i15 = 0; i15 <= loop_ub; i15++) {
      ugd->data[i15 + ugd->sizeX[0] * i14] = ug_cur->data[(i11 + i15) +
        ug_cur->sizeX[0] * i14];
    }
  }

  if (i == tileRows) {
    i11 = ug_cur->sizeX[1] - 1;
    for (i12 = 0; i12 <= i11; i12++) {
      ugd->data[((int32_T)blockSize + ugd->sizeX[0] * i12) - 1] = ug_cur->data
        [((int32_T)blockSize + ug_cur->sizeX[0] * i12) - 1];
    }
  } else {
    i11 = ug_dow->sizeX[1] - 1;
    for (i12 = 0; i12 <= i11; i12++) {
      ugd->data[((int32_T)blockSize + ugd->sizeX[0] * i12) - 1] = ug_dow->
        data[ug_dow->sizeX[0] * i12];
    }
  }

  b_emxInit_real_T(&ugl, 2);
  i11 = ugl->sizeX[0] * ugl->sizeX[1];
  ugl->sizeX[0] = (int32_T)blockSize;
  ugl->sizeX[1] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ugl, i11, (int32_T)sizeof(real_T));
  loop_ub = (int32_T)blockSize * (int32_T)blockSize - 1;
  for (i11 = 0; i11 <= loop_ub; i11++) {
    ugl->data[i11] = 0.0;
  }

  if (2.0 > blockSize) {
    i11 = 0;
    i12 = 0;
  } else {
    i11 = 1;
    i12 = (int32_T)blockSize;
  }

  i13 = ug_cur->sizeX[0] - 1;
  loop_ub = (i12 - i11) - 1;
  for (i12 = 0; i12 <= loop_ub; i12++) {
    for (i14 = 0; i14 <= i13; i14++) {
      ugl->data[i14 + ugl->sizeX[0] * i12] = ug_cur->data[i14 + ug_cur->sizeX[0] *
        (i11 + i12)];
    }
  }

  if (j == tileCols) {
    i11 = ug_cur->sizeX[0] - 1;
    for (i12 = 0; i12 <= i11; i12++) {
      ugl->data[i12 + ugl->sizeX[0] * ((int32_T)blockSize - 1)] = ug_cur->
        data[i12 + ug_cur->sizeX[0] * ((int32_T)blockSize - 1)];
    }
  } else {
    i11 = ug_lef->sizeX[0] - 1;
    for (i12 = 0; i12 <= i11; i12++) {
      ugl->data[i12 + ugl->sizeX[0] * ((int32_T)blockSize - 1)] = ug_lef->
        data[i12 + ug_lef->sizeX[0] * ((int32_T)blockSize - 1)];
    }
  }

  b_emxInit_real_T(&b_u_ij, 2);
  i11 = b_u_ij->sizeX[0] * b_u_ij->sizeX[1];
  b_u_ij->sizeX[0] = u_ij->sizeX[0];
  b_u_ij->sizeX[1] = u_ij->sizeX[1];
  emxEnsureCapacity((emxArray__common *)b_u_ij, i11, (int32_T)sizeof(real_T));
  loop_ub = u_ij->sizeX[0] * u_ij->sizeX[1] - 1;
  for (i11 = 0; i11 <= loop_ub; i11++) {
    b_u_ij->data[i11] = u_ij->data[i11] + 5.0 * ((((ugt->data[i11] + ugr->
      data[i11]) + ugd->data[i11]) + ugl->data[i11]) + b_gamma * (img_ij->
      data[i11] * r_ij->data[i11]));
  }

  emxFree_real_T(&ugl);
  emxFree_real_T(&ugd);
  emxFree_real_T(&ugr);
  emxFree_real_T(&ugt);
  b_emxInit_real_T(&r42, 2);
  i11 = r42->sizeX[0] * r42->sizeX[1];
  r42->sizeX[0] = gt->sizeX[0];
  r42->sizeX[1] = gt->sizeX[1];
  emxEnsureCapacity((emxArray__common *)r42, i11, (int32_T)sizeof(real_T));
  loop_ub = gt->sizeX[0] * gt->sizeX[1] - 1;
  for (i11 = 0; i11 <= loop_ub; i11++) {
    r42->data[i11] = 1.0 + 5.0 * ((((gt->data[i11] + gr->data[i11]) + gd->
      data[i11]) + gl->data[i11]) + b_gamma);
  }

  rdivide(b_u_ij, r42, u);
  emxFree_real_T(&r42);
  emxFree_real_T(&b_u_ij);
}

void ugStep(real_T blockSize, const emxArray_real_T *u_ij, const
                   emxArray_real_T *g_ij, emxArray_real_T *ug)
{
  int32_T i10;
  int32_T loop_ub;
  i10 = ug->sizeX[0] * ug->sizeX[1];
  ug->sizeX[0] = u_ij->sizeX[0];
  ug->sizeX[1] = u_ij->sizeX[1];
  emxEnsureCapacity((emxArray__common *)ug, i10, (int32_T)sizeof(real_T));
  loop_ub = u_ij->sizeX[0] * u_ij->sizeX[1] - 1;
  for (i10 = 0; i10 <= loop_ub; i10++) {
    ug->data[i10] = u_ij->data[i10] * g_ij->data[i10];
  }
}

void ricianDenoiseTiled(const emxArray_real_T *imageTiled, real_T blockSize,
  real_T sigma, real_T lambda, emxArray_real_T *u)
{
  real_T sigma2;
  real_T b_gamma;
  int32_T i0;
  int32_T loop_ub;
  emxArray_real_T *ut;
  int32_T nx;
  emxArray_real_T *ur;
  emxArray_real_T *ud;
  emxArray_real_T *ul;
  emxArray_real_T *g;
  emxArray_real_T *r;
  emxArray_real_T *ug;
  emxArray_real_T *ulast;
  emxArray_real_T *u_ij;
  emxArray_real_T *img_ij;
  emxArray_real_T *ug_cur;
  emxArray_real_T *ug_top;
  emxArray_real_T *ug_rig;
  emxArray_real_T *ug_dow;
  emxArray_real_T *ug_lef;
  emxArray_real_T *gt;
  emxArray_real_T *gr;
  emxArray_real_T *gd;
  emxArray_real_T *gl;
  emxArray_real_T *r_ij;
  emxArray_int32_T *r0;
  emxArray_int32_T *r1;
  emxArray_real_T *r2;
  emxArray_real_T *b_ug_cur;
  emxArray_real_T *b_ug_top;
  emxArray_real_T *b_ug_rig;
  emxArray_real_T *b_ug_dow;
  emxArray_real_T *c_ug_cur;
  emxArray_real_T *d_ug_cur;
  emxArray_real_T *e_ug_cur;
  emxArray_int32_T *r3;
  emxArray_int32_T *r4;
  emxArray_int32_T *r5;
  emxArray_int32_T *r6;
  emxArray_int32_T *r7;
  emxArray_int32_T *r8;
  emxArray_int32_T *r9;
  emxArray_int32_T *r10;
  emxArray_int32_T *r11;
  emxArray_int32_T *r12;
  emxArray_int32_T *r13;
  emxArray_int32_T *r14;
  emxArray_int32_T *r15;
  emxArray_int32_T *r16;
  emxArray_int32_T *r17;
  emxArray_int32_T *r18;
  emxArray_int32_T *r19;
  emxArray_int32_T *r20;
  emxArray_int32_T *r21;
  emxArray_int32_T *r22;
  emxArray_int32_T *r23;
  emxArray_int32_T *r24;
  emxArray_int32_T *r25;
  emxArray_int32_T *r26;
  emxArray_int32_T *r27;
  emxArray_int32_T *r28;
  emxArray_int32_T *r29;
  emxArray_int32_T *r30;
  emxArray_real_T *b_imageTiled;
  emxArray_real_T *b_ulast;
  emxArray_int32_T *r31;
  emxArray_int32_T *r32;
  emxArray_real_T *b_u;
  emxArray_real_T *c_imageTiled;
  emxArray_real_T *c_u;
  emxArray_int32_T *r33;
  emxArray_int32_T *r34;
  emxArray_int32_T *r35;
  emxArray_int32_T *r36;
  emxArray_int32_T *r37;
  emxArray_int32_T *r38;
  emxArray_int32_T *r39;
  emxArray_int32_T *r40;
  emxArray_real_T *d_u;
  emxArray_real_T *e_u;
  emxArray_real_T *f_u;
  emxArray_real_T *g_u;
  emxArray_real_T *h_u;
  emxArray_real_T *i_u;
  int32_T Iter;
  int32_T i;
  int32_T j;
  int32_T k;
  int32_T sz[2];
  real_T d0;
  int32_T i1;
  int32_T i2;
  int32_T b_loop_ub;
  int32_T b_sz[4];

  /*  Maximum allowed number of iterations */
  /*  Gradient descent time step sizeX */
  /*  Small parameter to avoid divide-by-zero */
  /* sigma2 = sigma ^ 2; */
  sigma2 = sigma * sigma;
  b_gamma = lambda / sigma2;

  /*  Initialize u as the input image */
  i0 = u->sizeX[0] * u->sizeX[1] * u->sizeX[2] * u->sizeX[3];
  u->sizeX[0] = imageTiled->sizeX[0];
  u->sizeX[1] = imageTiled->sizeX[1];
  u->sizeX[2] = imageTiled->sizeX[2];
  u->sizeX[3] = imageTiled->sizeX[3];
  emxEnsureCapacity((emxArray__common *)u, i0, (int32_T)sizeof(real_T));
  loop_ub = imageTiled->sizeX[0] * imageTiled->sizeX[1] * imageTiled->sizeX[2] *
    imageTiled->sizeX[3] - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    u->data[i0] = imageTiled->data[i0];
  }

  emxInit_real_T(&ut, 4);
  nx = imageTiled->sizeX[0];
  i0 = ut->sizeX[0] * ut->sizeX[1] * ut->sizeX[2] * ut->sizeX[3];
  ut->sizeX[0] = nx;
  emxEnsureCapacity((emxArray__common *)ut, i0, (int32_T)sizeof(real_T));
  nx = imageTiled->sizeX[1];
  i0 = ut->sizeX[0] * ut->sizeX[1] * ut->sizeX[2] * ut->sizeX[3];
  ut->sizeX[1] = nx;
  emxEnsureCapacity((emxArray__common *)ut, i0, (int32_T)sizeof(real_T));
  i0 = ut->sizeX[0] * ut->sizeX[1] * ut->sizeX[2] * ut->sizeX[3];
  ut->sizeX[2] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ut, i0, (int32_T)sizeof(real_T));
  i0 = ut->sizeX[0] * ut->sizeX[1] * ut->sizeX[2] * ut->sizeX[3];
  ut->sizeX[3] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ut, i0, (int32_T)sizeof(real_T));
  loop_ub = imageTiled->sizeX[0] * imageTiled->sizeX[1] * (int32_T)blockSize *
    (int32_T)blockSize - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    ut->data[i0] = 0.0;
  }

  emxInit_real_T(&ur, 4);
  nx = imageTiled->sizeX[0];
  i0 = ur->sizeX[0] * ur->sizeX[1] * ur->sizeX[2] * ur->sizeX[3];
  ur->sizeX[0] = nx;
  emxEnsureCapacity((emxArray__common *)ur, i0, (int32_T)sizeof(real_T));
  nx = imageTiled->sizeX[1];
  i0 = ur->sizeX[0] * ur->sizeX[1] * ur->sizeX[2] * ur->sizeX[3];
  ur->sizeX[1] = nx;
  emxEnsureCapacity((emxArray__common *)ur, i0, (int32_T)sizeof(real_T));
  i0 = ur->sizeX[0] * ur->sizeX[1] * ur->sizeX[2] * ur->sizeX[3];
  ur->sizeX[2] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ur, i0, (int32_T)sizeof(real_T));
  i0 = ur->sizeX[0] * ur->sizeX[1] * ur->sizeX[2] * ur->sizeX[3];
  ur->sizeX[3] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ur, i0, (int32_T)sizeof(real_T));
  loop_ub = imageTiled->sizeX[0] * imageTiled->sizeX[1] * (int32_T)blockSize *
    (int32_T)blockSize - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    ur->data[i0] = 0.0;
  }

  emxInit_real_T(&ud, 4);
  nx = imageTiled->sizeX[0];
  i0 = ud->sizeX[0] * ud->sizeX[1] * ud->sizeX[2] * ud->sizeX[3];
  ud->sizeX[0] = nx;
  emxEnsureCapacity((emxArray__common *)ud, i0, (int32_T)sizeof(real_T));
  nx = imageTiled->sizeX[1];
  i0 = ud->sizeX[0] * ud->sizeX[1] * ud->sizeX[2] * ud->sizeX[3];
  ud->sizeX[1] = nx;
  emxEnsureCapacity((emxArray__common *)ud, i0, (int32_T)sizeof(real_T));
  i0 = ud->sizeX[0] * ud->sizeX[1] * ud->sizeX[2] * ud->sizeX[3];
  ud->sizeX[2] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ud, i0, (int32_T)sizeof(real_T));
  i0 = ud->sizeX[0] * ud->sizeX[1] * ud->sizeX[2] * ud->sizeX[3];
  ud->sizeX[3] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ud, i0, (int32_T)sizeof(real_T));
  loop_ub = imageTiled->sizeX[0] * imageTiled->sizeX[1] * (int32_T)blockSize *
    (int32_T)blockSize - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    ud->data[i0] = 0.0;
  }

  emxInit_real_T(&ul, 4);
  nx = imageTiled->sizeX[0];
  i0 = ul->sizeX[0] * ul->sizeX[1] * ul->sizeX[2] * ul->sizeX[3];
  ul->sizeX[0] = nx;
  emxEnsureCapacity((emxArray__common *)ul, i0, (int32_T)sizeof(real_T));
  nx = imageTiled->sizeX[1];
  i0 = ul->sizeX[0] * ul->sizeX[1] * ul->sizeX[2] * ul->sizeX[3];
  ul->sizeX[1] = nx;
  emxEnsureCapacity((emxArray__common *)ul, i0, (int32_T)sizeof(real_T));
  i0 = ul->sizeX[0] * ul->sizeX[1] * ul->sizeX[2] * ul->sizeX[3];
  ul->sizeX[2] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ul, i0, (int32_T)sizeof(real_T));
  i0 = ul->sizeX[0] * ul->sizeX[1] * ul->sizeX[2] * ul->sizeX[3];
  ul->sizeX[3] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ul, i0, (int32_T)sizeof(real_T));
  loop_ub = imageTiled->sizeX[0] * imageTiled->sizeX[1] * (int32_T)blockSize *
    (int32_T)blockSize - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    ul->data[i0] = 0.0;
  }

  emxInit_real_T(&g, 4);
  nx = imageTiled->sizeX[0];
  i0 = g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * g->sizeX[3];
  g->sizeX[0] = nx;
  emxEnsureCapacity((emxArray__common *)g, i0, (int32_T)sizeof(real_T));
  nx = imageTiled->sizeX[1];
  i0 = g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * g->sizeX[3];
  g->sizeX[1] = nx;
  emxEnsureCapacity((emxArray__common *)g, i0, (int32_T)sizeof(real_T));
  i0 = g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * g->sizeX[3];
  g->sizeX[2] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)g, i0, (int32_T)sizeof(real_T));
  i0 = g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * g->sizeX[3];
  g->sizeX[3] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)g, i0, (int32_T)sizeof(real_T));
  loop_ub = imageTiled->sizeX[0] * imageTiled->sizeX[1] * (int32_T)blockSize *
    (int32_T)blockSize - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    g->data[i0] = 0.0;
  }

  emxInit_real_T(&r, 4);
  nx = imageTiled->sizeX[0];
  i0 = r->sizeX[0] * r->sizeX[1] * r->sizeX[2] * r->sizeX[3];
  r->sizeX[0] = nx;
  emxEnsureCapacity((emxArray__common *)r, i0, (int32_T)sizeof(real_T));
  nx = imageTiled->sizeX[1];
  i0 = r->sizeX[0] * r->sizeX[1] * r->sizeX[2] * r->sizeX[3];
  r->sizeX[1] = nx;
  emxEnsureCapacity((emxArray__common *)r, i0, (int32_T)sizeof(real_T));
  i0 = r->sizeX[0] * r->sizeX[1] * r->sizeX[2] * r->sizeX[3];
  r->sizeX[2] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)r, i0, (int32_T)sizeof(real_T));
  i0 = r->sizeX[0] * r->sizeX[1] * r->sizeX[2] * r->sizeX[3];
  r->sizeX[3] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)r, i0, (int32_T)sizeof(real_T));
  loop_ub = imageTiled->sizeX[0] * imageTiled->sizeX[1] * (int32_T)blockSize *
    (int32_T)blockSize - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    r->data[i0] = 0.0;
  }

  emxInit_real_T(&ug, 4);
  nx = imageTiled->sizeX[0];
  i0 = ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2] * ug->sizeX[3];
  ug->sizeX[0] = nx;
  emxEnsureCapacity((emxArray__common *)ug, i0, (int32_T)sizeof(real_T));
  nx = imageTiled->sizeX[1];
  i0 = ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2] * ug->sizeX[3];
  ug->sizeX[1] = nx;
  emxEnsureCapacity((emxArray__common *)ug, i0, (int32_T)sizeof(real_T));
  i0 = ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2] * ug->sizeX[3];
  ug->sizeX[2] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ug, i0, (int32_T)sizeof(real_T));
  i0 = ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2] * ug->sizeX[3];
  ug->sizeX[3] = (int32_T)blockSize;
  emxEnsureCapacity((emxArray__common *)ug, i0, (int32_T)sizeof(real_T));
  loop_ub = imageTiled->sizeX[0] * imageTiled->sizeX[1] * (int32_T)blockSize *
    (int32_T)blockSize - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    ug->data[i0] = 0.0;
  }

  /* %% Main gradient descent loop %%% */
  emxInit_real_T(&ulast, 4);
  b_emxInit_real_T(&u_ij, 2);
  b_emxInit_real_T(&img_ij, 2);
  b_emxInit_real_T(&ug_cur, 2);
  b_emxInit_real_T(&ug_top, 2);
  b_emxInit_real_T(&ug_rig, 2);
  b_emxInit_real_T(&ug_dow, 2);
  b_emxInit_real_T(&ug_lef, 2);
  b_emxInit_real_T(&gt, 2);
  b_emxInit_real_T(&gr, 2);
  b_emxInit_real_T(&gd, 2);
  b_emxInit_real_T(&gl, 2);
  b_emxInit_real_T(&r_ij, 2);
  emxInit_int32_T(&r0, 1);
  emxInit_int32_T(&r1, 1);
  emxInit_real_T(&r2, 4);
  b_emxInit_real_T(&b_ug_cur, 2);
  b_emxInit_real_T(&b_ug_top, 2);
  b_emxInit_real_T(&b_ug_rig, 2);
  b_emxInit_real_T(&b_ug_dow, 2);
  b_emxInit_real_T(&c_ug_cur, 2);
  b_emxInit_real_T(&d_ug_cur, 2);
  b_emxInit_real_T(&e_ug_cur, 2);
  emxInit_int32_T(&r3, 1);
  emxInit_int32_T(&r4, 1);
  emxInit_int32_T(&r5, 1);
  emxInit_int32_T(&r6, 1);
  emxInit_int32_T(&r7, 1);
  emxInit_int32_T(&r8, 1);
  emxInit_int32_T(&r9, 1);
  emxInit_int32_T(&r10, 1);
  emxInit_int32_T(&r11, 1);
  emxInit_int32_T(&r12, 1);
  emxInit_int32_T(&r13, 1);
  emxInit_int32_T(&r14, 1);
  emxInit_int32_T(&r15, 1);
  emxInit_int32_T(&r16, 1);
  emxInit_int32_T(&r17, 1);
  emxInit_int32_T(&r18, 1);
  emxInit_int32_T(&r19, 1);
  emxInit_int32_T(&r20, 1);
  emxInit_int32_T(&r21, 1);
  emxInit_int32_T(&r22, 1);
  emxInit_int32_T(&r23, 1);
  emxInit_int32_T(&r24, 1);
  emxInit_int32_T(&r25, 1);
  emxInit_int32_T(&r26, 1);
  emxInit_int32_T(&r27, 1);
  emxInit_int32_T(&r28, 1);
  emxInit_int32_T(&r29, 1);
  emxInit_int32_T(&r30, 1);
  emxInit_real_T(&b_imageTiled, 4);
  emxInit_real_T(&b_ulast, 4);
  emxInit_int32_T(&r31, 1);
  emxInit_int32_T(&r32, 1);
  emxInit_real_T(&b_u, 4);
  emxInit_real_T(&c_imageTiled, 4);
  emxInit_real_T(&c_u, 4);
  emxInit_int32_T(&r33, 1);
  emxInit_int32_T(&r34, 1);
  emxInit_int32_T(&r35, 1);
  emxInit_int32_T(&r36, 1);
  emxInit_int32_T(&r37, 1);
  emxInit_int32_T(&r38, 1);
  emxInit_int32_T(&r39, 1);
  emxInit_int32_T(&r40, 1);
  emxInit_real_T(&d_u, 4);
  emxInit_real_T(&e_u, 4);
  emxInit_real_T(&f_u, 4);
  emxInit_real_T(&g_u, 4);
  emxInit_real_T(&h_u, 4);
  emxInit_real_T(&i_u, 4);
  for (Iter = 0; Iter < 100; Iter++) {
    /*  value of u from the previous iteration */
    i0 = ulast->sizeX[0] * ulast->sizeX[1] * ulast->sizeX[2] * ulast->sizeX[3];
    ulast->sizeX[0] = u->sizeX[0];
    ulast->sizeX[1] = u->sizeX[1];
    ulast->sizeX[2] = u->sizeX[2];
    ulast->sizeX[3] = u->sizeX[3];
    emxEnsureCapacity((emxArray__common *)ulast, i0, (int32_T)sizeof(real_T));
    loop_ub = u->sizeX[0] * u->sizeX[1] * u->sizeX[2] * u->sizeX[3] - 1;
    for (i0 = 0; i0 <= loop_ub; i0++) {
      ulast->data[i0] = u->data[i0];
    }

    /*  Create shifted versions of the image */
    for (i = 0; i <= imageTiled->sizeX[0] - 1; i++) {
      for (j = 0; j <= imageTiled->sizeX[1] - 1; j++) {
        /*  Compute U offsets for top, right, down, and left. */
        nx = u->sizeX[2];
        k = u->sizeX[3];
        nx *= k;
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = ug_cur->sizeX[0] * ug_cur->sizeX[1];
        ug_cur->sizeX[0] = sz[0];
        ug_cur->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)ug_cur, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = u->sizeX[2];
          i1 = u->sizeX[3];
          i2 = i_u->sizeX[0] * i_u->sizeX[1] * i_u->sizeX[2] * i_u->sizeX[3];
          i_u->sizeX[0] = 1;
          i_u->sizeX[1] = 1;
          i_u->sizeX[2] = i0;
          i_u->sizeX[3] = i1;
          emxEnsureCapacity((emxArray__common *)i_u, i2, (int32_T)sizeof(real_T));
          loop_ub = i1 - 1;
          for (i1 = 0; i1 <= loop_ub; i1++) {
            b_loop_ub = i0 - 1;
            for (i2 = 0; i2 <= b_loop_ub; i2++) {
              i_u->data[i_u->sizeX[0] * i_u->sizeX[1] * i2 + i_u->sizeX[0] *
                i_u->sizeX[1] * i_u->sizeX[2] * i1] = u->data[((i + u->sizeX[0] * j)
                + u->sizeX[0] * u->sizeX[1] * i2) + u->sizeX[0] * u->sizeX[1] *
                u->sizeX[2] * i1];
            }
          }

          ug_cur->data[k] = i_u->data[k];
        }

        i0 = ug_top->sizeX[0] * ug_top->sizeX[1];
        ug_top->sizeX[0] = ug_cur->sizeX[0];
        ug_top->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)ug_top, i0, (int32_T)sizeof(real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          ug_top->data[i0] = ug_cur->data[i0];
        }

        if (1 + i > 1) {
          nx = u->sizeX[2];
          k = u->sizeX[3];
          nx *= k;
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = ug_top->sizeX[0] * ug_top->sizeX[1];
          ug_top->sizeX[0] = sz[0];
          ug_top->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)ug_top, i0, (int32_T)sizeof
                            (real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = u->sizeX[2];
            i1 = u->sizeX[3];
            i2 = h_u->sizeX[0] * h_u->sizeX[1] * h_u->sizeX[2] * h_u->sizeX[3];
            h_u->sizeX[0] = 1;
            h_u->sizeX[1] = 1;
            h_u->sizeX[2] = i0;
            h_u->sizeX[3] = i1;
            emxEnsureCapacity((emxArray__common *)h_u, i2, (int32_T)sizeof
                              (real_T));
            loop_ub = i1 - 1;
            for (i1 = 0; i1 <= loop_ub; i1++) {
              b_loop_ub = i0 - 1;
              for (i2 = 0; i2 <= b_loop_ub; i2++) {
                h_u->data[h_u->sizeX[0] * h_u->sizeX[1] * i2 + h_u->sizeX[0] *
                  h_u->sizeX[1] * h_u->sizeX[2] * i1] = u->data[(((i + u->sizeX[0] *
                  j) + u->sizeX[0] * u->sizeX[1] * i2) + u->sizeX[0] * u->sizeX[1] *
                  u->sizeX[2] * i1) - 1];
              }
            }

            ug_top->data[k] = h_u->data[k];
          }
        }

        i0 = ug_rig->sizeX[0] * ug_rig->sizeX[1];
        ug_rig->sizeX[0] = ug_cur->sizeX[0];
        ug_rig->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)ug_rig, i0, (int32_T)sizeof(real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          ug_rig->data[i0] = ug_cur->data[i0];
        }

        if (1 + j > 1) {
          nx = u->sizeX[2];
          k = u->sizeX[3];
          nx *= k;
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = ug_rig->sizeX[0] * ug_rig->sizeX[1];
          ug_rig->sizeX[0] = sz[0];
          ug_rig->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)ug_rig, i0, (int32_T)sizeof
                            (real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = u->sizeX[2];
            i1 = u->sizeX[3];
            i2 = g_u->sizeX[0] * g_u->sizeX[1] * g_u->sizeX[2] * g_u->sizeX[3];
            g_u->sizeX[0] = 1;
            g_u->sizeX[1] = 1;
            g_u->sizeX[2] = i0;
            g_u->sizeX[3] = i1;
            emxEnsureCapacity((emxArray__common *)g_u, i2, (int32_T)sizeof
                              (real_T));
            loop_ub = i1 - 1;
            for (i1 = 0; i1 <= loop_ub; i1++) {
              b_loop_ub = i0 - 1;
              for (i2 = 0; i2 <= b_loop_ub; i2++) {
                g_u->data[g_u->sizeX[0] * g_u->sizeX[1] * i2 + g_u->sizeX[0] *
                  g_u->sizeX[1] * g_u->sizeX[2] * i1] = u->data[((i + u->sizeX[0] *
                  (j - 1)) + u->sizeX[0] * u->sizeX[1] * i2) + u->sizeX[0] *
                  u->sizeX[1] * u->sizeX[2] * i1];
              }
            }

            ug_rig->data[k] = g_u->data[k];
          }
        }

        i0 = ug_dow->sizeX[0] * ug_dow->sizeX[1];
        ug_dow->sizeX[0] = ug_cur->sizeX[0];
        ug_dow->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)ug_dow, i0, (int32_T)sizeof(real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          ug_dow->data[i0] = ug_cur->data[i0];
        }

        if (1 + i < imageTiled->sizeX[0]) {
          nx = u->sizeX[2];
          k = u->sizeX[3];
          nx *= k;
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = ug_dow->sizeX[0] * ug_dow->sizeX[1];
          ug_dow->sizeX[0] = sz[0];
          ug_dow->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)ug_dow, i0, (int32_T)sizeof
                            (real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = u->sizeX[2];
            i1 = u->sizeX[3];
            i2 = f_u->sizeX[0] * f_u->sizeX[1] * f_u->sizeX[2] * f_u->sizeX[3];
            f_u->sizeX[0] = 1;
            f_u->sizeX[1] = 1;
            f_u->sizeX[2] = i0;
            f_u->sizeX[3] = i1;
            emxEnsureCapacity((emxArray__common *)f_u, i2, (int32_T)sizeof
                              (real_T));
            loop_ub = i1 - 1;
            for (i1 = 0; i1 <= loop_ub; i1++) {
              b_loop_ub = i0 - 1;
              for (i2 = 0; i2 <= b_loop_ub; i2++) {
                f_u->data[f_u->sizeX[0] * f_u->sizeX[1] * i2 + f_u->sizeX[0] *
                  f_u->sizeX[1] * f_u->sizeX[2] * i1] = u->data[(((i + u->sizeX[0] *
                  j) + u->sizeX[0] * u->sizeX[1] * i2) + u->sizeX[0] * u->sizeX[1] *
                  u->sizeX[2] * i1) + 1];
              }
            }

            ug_dow->data[k] = f_u->data[k];
          }
        }

        i0 = ug_lef->sizeX[0] * ug_lef->sizeX[1];
        ug_lef->sizeX[0] = ug_cur->sizeX[0];
        ug_lef->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)ug_lef, i0, (int32_T)sizeof(real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          ug_lef->data[i0] = ug_cur->data[i0];
        }

        if (1 + j < imageTiled->sizeX[1]) {
          nx = u->sizeX[2];
          k = u->sizeX[3];
          nx *= k;
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = ug_lef->sizeX[0] * ug_lef->sizeX[1];
          ug_lef->sizeX[0] = sz[0];
          ug_lef->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)ug_lef, i0, (int32_T)sizeof
                            (real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = u->sizeX[2];
            i1 = u->sizeX[3];
            i2 = e_u->sizeX[0] * e_u->sizeX[1] * e_u->sizeX[2] * e_u->sizeX[3];
            e_u->sizeX[0] = 1;
            e_u->sizeX[1] = 1;
            e_u->sizeX[2] = i0;
            e_u->sizeX[3] = i1;
            emxEnsureCapacity((emxArray__common *)e_u, i2, (int32_T)sizeof
                              (real_T));
            loop_ub = i1 - 1;
            for (i1 = 0; i1 <= loop_ub; i1++) {
              b_loop_ub = i0 - 1;
              for (i2 = 0; i2 <= b_loop_ub; i2++) {
                e_u->data[e_u->sizeX[0] * e_u->sizeX[1] * i2 + e_u->sizeX[0] *
                  e_u->sizeX[1] * e_u->sizeX[2] * i1] = u->data[((i + u->sizeX[0] *
                  (j + 1)) + u->sizeX[0] * u->sizeX[1] * i2) + u->sizeX[0] *
                  u->sizeX[1] * u->sizeX[2] * i1];
              }
            }

            ug_lef->data[k] = e_u->data[k];
          }
        }

        i0 = b_ug_cur->sizeX[0] * b_ug_cur->sizeX[1];
        b_ug_cur->sizeX[0] = ug_cur->sizeX[0];
        b_ug_cur->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)b_ug_cur, i0, (int32_T)sizeof
                          (real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_ug_cur->data[i0] = ug_cur->data[i0];
        }

        i0 = b_ug_top->sizeX[0] * b_ug_top->sizeX[1];
        b_ug_top->sizeX[0] = ug_top->sizeX[0];
        b_ug_top->sizeX[1] = ug_top->sizeX[1];
        emxEnsureCapacity((emxArray__common *)b_ug_top, i0, (int32_T)sizeof
                          (real_T));
        loop_ub = ug_top->sizeX[0] * ug_top->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_ug_top->data[i0] = ug_top->data[i0];
        }

        i0 = b_ug_rig->sizeX[0] * b_ug_rig->sizeX[1];
        b_ug_rig->sizeX[0] = ug_rig->sizeX[0];
        b_ug_rig->sizeX[1] = ug_rig->sizeX[1];
        emxEnsureCapacity((emxArray__common *)b_ug_rig, i0, (int32_T)sizeof
                          (real_T));
        loop_ub = ug_rig->sizeX[0] * ug_rig->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_ug_rig->data[i0] = ug_rig->data[i0];
        }

        i0 = b_ug_dow->sizeX[0] * b_ug_dow->sizeX[1];
        b_ug_dow->sizeX[0] = ug_dow->sizeX[0];
        b_ug_dow->sizeX[1] = ug_dow->sizeX[1];
        emxEnsureCapacity((emxArray__common *)b_ug_dow, i0, (int32_T)sizeof
                          (real_T));
        loop_ub = ug_dow->sizeX[0] * ug_dow->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_ug_dow->data[i0] = ug_dow->data[i0];
        }

        uDiffStep(1.0 + (real_T)i, 1.0 + (real_T)j, blockSize, (real_T)
                  imageTiled->sizeX[0], (real_T)imageTiled->sizeX[1], b_ug_cur,
                  b_ug_top, b_ug_rig, b_ug_dow, ug_lef, ug_cur, ug_top, ug_rig,
                  ug_dow);
        i0 = ut->sizeX[2];
        i1 = r0->sizeX[0];
        r0->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r0, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r0->data[i0] = i0;
        }

        i0 = ut->sizeX[3];
        i1 = r1->sizeX[0];
        r1->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r1, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r1->data[i0] = i0;
        }

        k = r0->sizeX[0];
        nx = r1->sizeX[0];
        loop_ub = nx - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_loop_ub = k - 1;
          for (i1 = 0; i1 <= b_loop_ub; i1++) {
            i2 = 0;
            while (i2 <= 0) {
              i2 = 0;
              while (i2 <= 0) {
                ut->data[((i + ut->sizeX[0] * j) + ut->sizeX[0] * ut->sizeX[1] *
                          r0->data[i1]) + ut->sizeX[0] * ut->sizeX[1] * ut->sizeX[2]
                  * r1->data[i0]] = ug_cur->data[i1 + k * i0];
                i2 = 1;
              }

              i2 = 1;
            }
          }
        }

        i0 = ur->sizeX[2];
        i1 = r0->sizeX[0];
        r0->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r0, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r0->data[i0] = i0;
        }

        i0 = ur->sizeX[3];
        i1 = r1->sizeX[0];
        r1->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r1, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r1->data[i0] = i0;
        }

        k = r0->sizeX[0];
        nx = r1->sizeX[0];
        loop_ub = nx - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_loop_ub = k - 1;
          for (i1 = 0; i1 <= b_loop_ub; i1++) {
            i2 = 0;
            while (i2 <= 0) {
              i2 = 0;
              while (i2 <= 0) {
                ur->data[((i + ur->sizeX[0] * j) + ur->sizeX[0] * ur->sizeX[1] *
                          r0->data[i1]) + ur->sizeX[0] * ur->sizeX[1] * ur->sizeX[2]
                  * r1->data[i0]] = ug_top->data[i1 + k * i0];
                i2 = 1;
              }

              i2 = 1;
            }
          }
        }

        i0 = ud->sizeX[2];
        i1 = r0->sizeX[0];
        r0->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r0, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r0->data[i0] = i0;
        }

        i0 = ud->sizeX[3];
        i1 = r1->sizeX[0];
        r1->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r1, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r1->data[i0] = i0;
        }

        k = r0->sizeX[0];
        nx = r1->sizeX[0];
        loop_ub = nx - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_loop_ub = k - 1;
          for (i1 = 0; i1 <= b_loop_ub; i1++) {
            i2 = 0;
            while (i2 <= 0) {
              i2 = 0;
              while (i2 <= 0) {
                ud->data[((i + ud->sizeX[0] * j) + ud->sizeX[0] * ud->sizeX[1] *
                          r0->data[i1]) + ud->sizeX[0] * ud->sizeX[1] * ud->sizeX[2]
                  * r1->data[i0]] = ug_rig->data[i1 + k * i0];
                i2 = 1;
              }

              i2 = 1;
            }
          }
        }

        i0 = ul->sizeX[2];
        i1 = r0->sizeX[0];
        r0->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r0, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r0->data[i0] = i0;
        }

        i0 = ul->sizeX[3];
        i1 = r1->sizeX[0];
        r1->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r1, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r1->data[i0] = i0;
        }

        k = r0->sizeX[0];
        nx = r1->sizeX[0];
        loop_ub = nx - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_loop_ub = k - 1;
          for (i1 = 0; i1 <= b_loop_ub; i1++) {
            i2 = 0;
            while (i2 <= 0) {
              i2 = 0;
              while (i2 <= 0) {
                ul->data[((i + ul->sizeX[0] * j) + ul->sizeX[0] * ul->sizeX[1] *
                          r0->data[i1]) + ul->sizeX[0] * ul->sizeX[1] * ul->sizeX[2]
                  * r1->data[i0]] = ug_dow->data[i1 + k * i0];
                i2 = 1;
              }

              i2 = 1;
            }
          }
        }
      }
    }

    for (i = 0; i <= imageTiled->sizeX[0] - 1; i++) {
      for (j = 0; j <= imageTiled->sizeX[1] - 1; j++) {
        /*  Compute G */
        nx = u->sizeX[2];
        k = u->sizeX[3];
        nx *= k;
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = u_ij->sizeX[0] * u_ij->sizeX[1];
        u_ij->sizeX[0] = sz[0];
        u_ij->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)u_ij, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = u->sizeX[2];
          i1 = u->sizeX[3];
          i2 = d_u->sizeX[0] * d_u->sizeX[1] * d_u->sizeX[2] * d_u->sizeX[3];
          d_u->sizeX[0] = 1;
          d_u->sizeX[1] = 1;
          d_u->sizeX[2] = i0;
          d_u->sizeX[3] = i1;
          emxEnsureCapacity((emxArray__common *)d_u, i2, (int32_T)sizeof(real_T));
          loop_ub = i1 - 1;
          for (i1 = 0; i1 <= loop_ub; i1++) {
            b_loop_ub = i0 - 1;
            for (i2 = 0; i2 <= b_loop_ub; i2++) {
              d_u->data[d_u->sizeX[0] * d_u->sizeX[1] * i2 + d_u->sizeX[0] *
                d_u->sizeX[1] * d_u->sizeX[2] * i1] = u->data[((i + u->sizeX[0] * j)
                + u->sizeX[0] * u->sizeX[1] * i2) + u->sizeX[0] * u->sizeX[1] *
                u->sizeX[2] * i1];
            }
          }

          u_ij->data[k] = d_u->data[k];
        }

        i0 = ut->sizeX[2];
        i1 = r33->sizeX[0];
        r33->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r33, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r33->data[i0] = 1 + i0;
        }

        i0 = ut->sizeX[3];
        i1 = r34->sizeX[0];
        r34->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r34, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r34->data[i0] = 1 + i0;
        }

        nx = r33->sizeX[0] * r34->sizeX[0];
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = ug_cur->sizeX[0] * ug_cur->sizeX[1];
        ug_cur->sizeX[0] = sz[0];
        ug_cur->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)ug_cur, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = ut->sizeX[2];
          ug_cur->data[k] = ut->data[((i + ut->sizeX[0] * j) + ut->sizeX[0] *
            ut->sizeX[1] * (k % i0)) + ut->sizeX[0] * ut->sizeX[1] * ut->sizeX[2] *
            (k / i0)];
        }

        i0 = ur->sizeX[2];
        i1 = r35->sizeX[0];
        r35->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r35, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r35->data[i0] = 1 + i0;
        }

        i0 = ur->sizeX[3];
        i1 = r36->sizeX[0];
        r36->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r36, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r36->data[i0] = 1 + i0;
        }

        nx = r35->sizeX[0] * r36->sizeX[0];
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = ug_top->sizeX[0] * ug_top->sizeX[1];
        ug_top->sizeX[0] = sz[0];
        ug_top->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)ug_top, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = ur->sizeX[2];
          ug_top->data[k] = ur->data[((i + ur->sizeX[0] * j) + ur->sizeX[0] *
            ur->sizeX[1] * (k % i0)) + ur->sizeX[0] * ur->sizeX[1] * ur->sizeX[2] *
            (k / i0)];
        }

        i0 = ud->sizeX[2];
        i1 = r37->sizeX[0];
        r37->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r37, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r37->data[i0] = 1 + i0;
        }

        i0 = ud->sizeX[3];
        i1 = r38->sizeX[0];
        r38->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r38, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r38->data[i0] = 1 + i0;
        }

        nx = r37->sizeX[0] * r38->sizeX[0];
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = ug_rig->sizeX[0] * ug_rig->sizeX[1];
        ug_rig->sizeX[0] = sz[0];
        ug_rig->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)ug_rig, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = ud->sizeX[2];
          ug_rig->data[k] = ud->data[((i + ud->sizeX[0] * j) + ud->sizeX[0] *
            ud->sizeX[1] * (k % i0)) + ud->sizeX[0] * ud->sizeX[1] * ud->sizeX[2] *
            (k / i0)];
        }

        i0 = ul->sizeX[2];
        i1 = r39->sizeX[0];
        r39->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r39, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r39->data[i0] = 1 + i0;
        }

        i0 = ul->sizeX[3];
        i1 = r40->sizeX[0];
        r40->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r40, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r40->data[i0] = 1 + i0;
        }

        nx = r39->sizeX[0] * r40->sizeX[0];
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = ug_dow->sizeX[0] * ug_dow->sizeX[1];
        ug_dow->sizeX[0] = sz[0];
        ug_dow->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)ug_dow, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = ul->sizeX[2];
          ug_dow->data[k] = ul->data[((i + ul->sizeX[0] * j) + ul->sizeX[0] *
            ul->sizeX[1] * (k % i0)) + ul->sizeX[0] * ul->sizeX[1] * ul->sizeX[2] *
            (k / i0)];
        }

        i0 = c_ug_cur->sizeX[0] * c_ug_cur->sizeX[1];
        c_ug_cur->sizeX[0] = ug_cur->sizeX[0];
        c_ug_cur->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)c_ug_cur, i0, (int32_T)sizeof
                          (real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          c_ug_cur->data[i0] = ug_cur->data[i0];
        }

        gStep(blockSize, u_ij, c_ug_cur, ug_top, ug_rig, ug_dow, ug_cur);
        nx = ug_cur->sizeX[0] * ug_cur->sizeX[1];
        for (i0 = 0; i0 < 4; i0++) {
          b_sz[i0] = 0;
        }

        b_sz[0] = 1;
        b_sz[1] = 1;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        b_sz[2] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        b_sz[3] = i0;
        i0 = r2->sizeX[0] * r2->sizeX[1] * r2->sizeX[2] * r2->sizeX[3];
        r2->sizeX[0] = 1;
        r2->sizeX[1] = 1;
        r2->sizeX[2] = b_sz[2];
        r2->sizeX[3] = b_sz[3];
        emxEnsureCapacity((emxArray__common *)r2, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          r2->data[k] = ug_cur->data[k];
        }

        loop_ub = r2->sizeX[3] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_loop_ub = r2->sizeX[2] - 1;
          for (i1 = 0; i1 <= b_loop_ub; i1++) {
            g->data[((i + g->sizeX[0] * j) + g->sizeX[0] * g->sizeX[1] * i1) +
              g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * i0] = r2->data[r2->sizeX[0] *
              r2->sizeX[1] * i1 + r2->sizeX[0] * r2->sizeX[1] * r2->sizeX[2] * i0];
          }
        }
      }
    }

    for (i = 0; i <= imageTiled->sizeX[0] - 1; i++) {
      for (j = 0; j <= imageTiled->sizeX[1] - 1; j++) {
        /*  Compute R */
        nx = u->sizeX[2];
        k = u->sizeX[3];
        nx *= k;
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = u_ij->sizeX[0] * u_ij->sizeX[1];
        u_ij->sizeX[0] = sz[0];
        u_ij->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)u_ij, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = u->sizeX[2];
          i1 = u->sizeX[3];
          i2 = c_u->sizeX[0] * c_u->sizeX[1] * c_u->sizeX[2] * c_u->sizeX[3];
          c_u->sizeX[0] = 1;
          c_u->sizeX[1] = 1;
          c_u->sizeX[2] = i0;
          c_u->sizeX[3] = i1;
          emxEnsureCapacity((emxArray__common *)c_u, i2, (int32_T)sizeof(real_T));
          loop_ub = i1 - 1;
          for (i1 = 0; i1 <= loop_ub; i1++) {
            b_loop_ub = i0 - 1;
            for (i2 = 0; i2 <= b_loop_ub; i2++) {
              c_u->data[c_u->sizeX[0] * c_u->sizeX[1] * i2 + c_u->sizeX[0] *
                c_u->sizeX[1] * c_u->sizeX[2] * i1] = u->data[((i + u->sizeX[0] * j)
                + u->sizeX[0] * u->sizeX[1] * i2) + u->sizeX[0] * u->sizeX[1] *
                u->sizeX[2] * i1];
            }
          }

          u_ij->data[k] = c_u->data[k];
        }

        nx = imageTiled->sizeX[2];
        k = imageTiled->sizeX[3];
        nx *= k;
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = img_ij->sizeX[0] * img_ij->sizeX[1];
        img_ij->sizeX[0] = sz[0];
        img_ij->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)img_ij, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = imageTiled->sizeX[2];
          i1 = imageTiled->sizeX[3];
          i2 = c_imageTiled->sizeX[0] * c_imageTiled->sizeX[1] *
            c_imageTiled->sizeX[2] * c_imageTiled->sizeX[3];
          c_imageTiled->sizeX[0] = 1;
          c_imageTiled->sizeX[1] = 1;
          c_imageTiled->sizeX[2] = i0;
          c_imageTiled->sizeX[3] = i1;
          emxEnsureCapacity((emxArray__common *)c_imageTiled, i2, (int32_T)
                            sizeof(real_T));
          loop_ub = i1 - 1;
          for (i1 = 0; i1 <= loop_ub; i1++) {
            b_loop_ub = i0 - 1;
            for (i2 = 0; i2 <= b_loop_ub; i2++) {
              c_imageTiled->data[c_imageTiled->sizeX[0] * c_imageTiled->sizeX[1] *
                i2 + c_imageTiled->sizeX[0] * c_imageTiled->sizeX[1] *
                c_imageTiled->sizeX[2] * i1] = imageTiled->data[((i +
                imageTiled->sizeX[0] * j) + imageTiled->sizeX[0] *
                imageTiled->sizeX[1] * i2) + imageTiled->sizeX[0] *
                imageTiled->sizeX[1] * imageTiled->sizeX[2] * i1];
            }
          }

          img_ij->data[k] = c_imageTiled->data[k];
        }

        rStep(blockSize, u_ij, img_ij, sigma2, ug_cur);
        nx = ug_cur->sizeX[0] * ug_cur->sizeX[1];
        for (i0 = 0; i0 < 4; i0++) {
          b_sz[i0] = 0;
        }

        b_sz[0] = 1;
        b_sz[1] = 1;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        b_sz[2] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        b_sz[3] = i0;
        i0 = r2->sizeX[0] * r2->sizeX[1] * r2->sizeX[2] * r2->sizeX[3];
        r2->sizeX[0] = 1;
        r2->sizeX[1] = 1;
        r2->sizeX[2] = b_sz[2];
        r2->sizeX[3] = b_sz[3];
        emxEnsureCapacity((emxArray__common *)r2, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          r2->data[k] = ug_cur->data[k];
        }

        loop_ub = r2->sizeX[3] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_loop_ub = r2->sizeX[2] - 1;
          for (i1 = 0; i1 <= b_loop_ub; i1++) {
            r->data[((i + r->sizeX[0] * j) + r->sizeX[0] * r->sizeX[1] * i1) +
              r->sizeX[0] * r->sizeX[1] * r->sizeX[2] * i0] = r2->data[r2->sizeX[0] *
              r2->sizeX[1] * i1 + r2->sizeX[0] * r2->sizeX[1] * r2->sizeX[2] * i0];
          }
        }
      }
    }

    for (i = 0; i <= imageTiled->sizeX[0] - 1; i++) {
      for (j = 0; j <= imageTiled->sizeX[1] - 1; j++) {
        /*  Compute UG */
        /*  Update u by a semi-implicit step */
        nx = u->sizeX[2];
        k = u->sizeX[3];
        nx *= k;
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = u_ij->sizeX[0] * u_ij->sizeX[1];
        u_ij->sizeX[0] = sz[0];
        u_ij->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)u_ij, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = u->sizeX[2];
          i1 = u->sizeX[3];
          i2 = b_u->sizeX[0] * b_u->sizeX[1] * b_u->sizeX[2] * b_u->sizeX[3];
          b_u->sizeX[0] = 1;
          b_u->sizeX[1] = 1;
          b_u->sizeX[2] = i0;
          b_u->sizeX[3] = i1;
          emxEnsureCapacity((emxArray__common *)b_u, i2, (int32_T)sizeof(real_T));
          loop_ub = i1 - 1;
          for (i1 = 0; i1 <= loop_ub; i1++) {
            b_loop_ub = i0 - 1;
            for (i2 = 0; i2 <= b_loop_ub; i2++) {
              b_u->data[b_u->sizeX[0] * b_u->sizeX[1] * i2 + b_u->sizeX[0] *
                b_u->sizeX[1] * b_u->sizeX[2] * i1] = u->data[((i + u->sizeX[0] * j)
                + u->sizeX[0] * u->sizeX[1] * i2) + u->sizeX[0] * u->sizeX[1] *
                u->sizeX[2] * i1];
            }
          }

          u_ij->data[k] = b_u->data[k];
        }

        i0 = g->sizeX[2];
        i1 = r31->sizeX[0];
        r31->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r31, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r31->data[i0] = 1 + i0;
        }

        i0 = g->sizeX[3];
        i1 = r32->sizeX[0];
        r32->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r32, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r32->data[i0] = 1 + i0;
        }

        nx = r31->sizeX[0] * r32->sizeX[0];
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = ug_cur->sizeX[0] * ug_cur->sizeX[1];
        ug_cur->sizeX[0] = sz[0];
        ug_cur->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)ug_cur, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = g->sizeX[2];
          ug_cur->data[k] = g->data[((i + g->sizeX[0] * j) + g->sizeX[0] * g->
            sizeX[1] * (k % i0)) + g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * (k / i0)];
        }

        /*  call ugStep */
        i0 = d_ug_cur->sizeX[0] * d_ug_cur->sizeX[1];
        d_ug_cur->sizeX[0] = ug_cur->sizeX[0];
        d_ug_cur->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)d_ug_cur, i0, (int32_T)sizeof
                          (real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          d_ug_cur->data[i0] = ug_cur->data[i0];
        }

        ugStep(blockSize, u_ij, d_ug_cur, ug_cur);
        nx = ug_cur->sizeX[0] * ug_cur->sizeX[1];
        for (i0 = 0; i0 < 4; i0++) {
          b_sz[i0] = 0;
        }

        b_sz[0] = 1;
        b_sz[1] = 1;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        b_sz[2] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        b_sz[3] = i0;
        i0 = r2->sizeX[0] * r2->sizeX[1] * r2->sizeX[2] * r2->sizeX[3];
        r2->sizeX[0] = 1;
        r2->sizeX[1] = 1;
        r2->sizeX[2] = b_sz[2];
        r2->sizeX[3] = b_sz[3];
        emxEnsureCapacity((emxArray__common *)r2, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          r2->data[k] = ug_cur->data[k];
        }

        loop_ub = r2->sizeX[3] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_loop_ub = r2->sizeX[2] - 1;
          for (i1 = 0; i1 <= b_loop_ub; i1++) {
            ug->data[((i + ug->sizeX[0] * j) + ug->sizeX[0] * ug->sizeX[1] * i1) +
              ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2] * i0] = r2->data[r2->sizeX
              [0] * r2->sizeX[1] * i1 + r2->sizeX[0] * r2->sizeX[1] * r2->sizeX[2] *
              i0];
          }
        }
      }
    }

    for (i = 0; i <= imageTiled->sizeX[0] - 1; i++) {
      for (j = 0; j <= imageTiled->sizeX[1] - 1; j++) {
        /*  Compute U */
        i0 = ug->sizeX[2];
        i1 = r3->sizeX[0];
        r3->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r3, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r3->data[i0] = 1 + i0;
        }

        i0 = ug->sizeX[3];
        i1 = r4->sizeX[0];
        r4->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r4, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r4->data[i0] = 1 + i0;
        }

        nx = r3->sizeX[0] * r4->sizeX[0];
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = ug_cur->sizeX[0] * ug_cur->sizeX[1];
        ug_cur->sizeX[0] = sz[0];
        ug_cur->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)ug_cur, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = ug->sizeX[2];
          ug_cur->data[k] = ug->data[((i + ug->sizeX[0] * j) + ug->sizeX[0] *
            ug->sizeX[1] * (k % i0)) + ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2] *
            (k / i0)];
        }

        i0 = ug_top->sizeX[0] * ug_top->sizeX[1];
        ug_top->sizeX[0] = ug_cur->sizeX[0];
        ug_top->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)ug_top, i0, (int32_T)sizeof(real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          ug_top->data[i0] = ug_cur->data[i0];
        }

        if (1 + i > 1) {
          i0 = ug->sizeX[2];
          i1 = r5->sizeX[0];
          r5->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r5, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r5->data[i0] = 1 + i0;
          }

          i0 = ug->sizeX[3];
          i1 = r6->sizeX[0];
          r6->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r6, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r6->data[i0] = 1 + i0;
          }

          nx = r5->sizeX[0] * r6->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = ug_top->sizeX[0] * ug_top->sizeX[1];
          ug_top->sizeX[0] = sz[0];
          ug_top->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)ug_top, i0, (int32_T)sizeof
                            (real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = ug->sizeX[2];
            ug_top->data[k] = ug->data[(((i + ug->sizeX[0] * j) + ug->sizeX[0] *
              ug->sizeX[1] * (k % i0)) + ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2] *
                                        (k / i0)) - 1];
          }
        }

        i0 = ug_rig->sizeX[0] * ug_rig->sizeX[1];
        ug_rig->sizeX[0] = ug_cur->sizeX[0];
        ug_rig->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)ug_rig, i0, (int32_T)sizeof(real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          ug_rig->data[i0] = ug_cur->data[i0];
        }

        if (1 + j > 1) {
          i0 = ug->sizeX[2];
          i1 = r7->sizeX[0];
          r7->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r7, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r7->data[i0] = 1 + i0;
          }

          i0 = ug->sizeX[3];
          i1 = r8->sizeX[0];
          r8->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r8, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r8->data[i0] = 1 + i0;
          }

          nx = r7->sizeX[0] * r8->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = ug_rig->sizeX[0] * ug_rig->sizeX[1];
          ug_rig->sizeX[0] = sz[0];
          ug_rig->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)ug_rig, i0, (int32_T)sizeof
                            (real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = ug->sizeX[2];
            ug_rig->data[k] = ug->data[((i + ug->sizeX[0] * (j - 1)) + ug->sizeX[0]
              * ug->sizeX[1] * (k % i0)) + ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2]
              * (k / i0)];
          }
        }

        i0 = ug_dow->sizeX[0] * ug_dow->sizeX[1];
        ug_dow->sizeX[0] = ug_cur->sizeX[0];
        ug_dow->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)ug_dow, i0, (int32_T)sizeof(real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          ug_dow->data[i0] = ug_cur->data[i0];
        }

        if (1 + i < imageTiled->sizeX[0]) {
          i0 = ug->sizeX[2];
          i1 = r9->sizeX[0];
          r9->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r9, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r9->data[i0] = 1 + i0;
          }

          i0 = ug->sizeX[3];
          i1 = r10->sizeX[0];
          r10->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r10, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r10->data[i0] = 1 + i0;
          }

          nx = r9->sizeX[0] * r10->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = ug_dow->sizeX[0] * ug_dow->sizeX[1];
          ug_dow->sizeX[0] = sz[0];
          ug_dow->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)ug_dow, i0, (int32_T)sizeof
                            (real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = ug->sizeX[2];
            ug_dow->data[k] = ug->data[(((i + ug->sizeX[0] * j) + ug->sizeX[0] *
              ug->sizeX[1] * (k % i0)) + ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2] *
                                        (k / i0)) + 1];
          }
        }

        i0 = ug_lef->sizeX[0] * ug_lef->sizeX[1];
        ug_lef->sizeX[0] = ug_cur->sizeX[0];
        ug_lef->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)ug_lef, i0, (int32_T)sizeof(real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          ug_lef->data[i0] = ug_cur->data[i0];
        }

        if (1 + j < imageTiled->sizeX[1]) {
          i0 = ug->sizeX[2];
          i1 = r11->sizeX[0];
          r11->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r11, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r11->data[i0] = 1 + i0;
          }

          i0 = ug->sizeX[3];
          i1 = r12->sizeX[0];
          r12->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r12, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r12->data[i0] = 1 + i0;
          }

          nx = r11->sizeX[0] * r12->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = ug_lef->sizeX[0] * ug_lef->sizeX[1];
          ug_lef->sizeX[0] = sz[0];
          ug_lef->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)ug_lef, i0, (int32_T)sizeof
                            (real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = ug->sizeX[2];
            ug_lef->data[k] = ug->data[((i + ug->sizeX[0] * (j + 1)) + ug->sizeX[0]
              * ug->sizeX[1] * (k % i0)) + ug->sizeX[0] * ug->sizeX[1] * ug->sizeX[2]
              * (k / i0)];
          }
        }

        /*  gt = zeros(tileRows, tileCols); */
        if (1 + i == 1) {
          i0 = g->sizeX[2];
          i1 = r15->sizeX[0];
          r15->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r15, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r15->data[i0] = 1 + i0;
          }

          i0 = g->sizeX[3];
          i1 = r16->sizeX[0];
          r16->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r16, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r16->data[i0] = 1 + i0;
          }

          nx = r15->sizeX[0] * r16->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = gt->sizeX[0] * gt->sizeX[1];
          gt->sizeX[0] = sz[0];
          gt->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)gt, i0, (int32_T)sizeof(real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = g->sizeX[2];
            gt->data[k] = g->data[(g->sizeX[0] * j + g->sizeX[0] * g->sizeX[1] * (k
              % i0)) + g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * (k / i0)];
          }
        } else {
          i0 = g->sizeX[2];
          i1 = r13->sizeX[0];
          r13->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r13, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r13->data[i0] = 1 + i0;
          }

          i0 = g->sizeX[3];
          i1 = r14->sizeX[0];
          r14->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r14, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r14->data[i0] = 1 + i0;
          }

          nx = r13->sizeX[0] * r14->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = gt->sizeX[0] * gt->sizeX[1];
          gt->sizeX[0] = sz[0];
          gt->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)gt, i0, (int32_T)sizeof(real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = g->sizeX[2];
            gt->data[k] = g->data[(((i + g->sizeX[0] * j) + g->sizeX[0] * g->sizeX
              [1] * (k % i0)) + g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * (k / i0))
              - 1];
          }
        }

        /*  gr = zeros(tileRows, tileCols); */
        if (1 + j == 1) {
          i0 = g->sizeX[2];
          i1 = r19->sizeX[0];
          r19->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r19, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r19->data[i0] = 1 + i0;
          }

          i0 = g->sizeX[3];
          i1 = r20->sizeX[0];
          r20->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r20, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r20->data[i0] = 1 + i0;
          }

          nx = r19->sizeX[0] * r20->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = gr->sizeX[0] * gr->sizeX[1];
          gr->sizeX[0] = sz[0];
          gr->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)gr, i0, (int32_T)sizeof(real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = g->sizeX[2];
            gr->data[k] = g->data[(i + g->sizeX[0] * g->sizeX[1] * (k % i0)) +
              g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * (k / i0)];
          }
        } else {
          i0 = g->sizeX[2];
          i1 = r17->sizeX[0];
          r17->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r17, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r17->data[i0] = 1 + i0;
          }

          i0 = g->sizeX[3];
          i1 = r18->sizeX[0];
          r18->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r18, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r18->data[i0] = 1 + i0;
          }

          nx = r17->sizeX[0] * r18->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = gr->sizeX[0] * gr->sizeX[1];
          gr->sizeX[0] = sz[0];
          gr->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)gr, i0, (int32_T)sizeof(real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = g->sizeX[2];
            gr->data[k] = g->data[((i + g->sizeX[0] * (j - 1)) + g->sizeX[0] *
              g->sizeX[1] * (k % i0)) + g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * (k
              / i0)];
          }
        }

        /*  gd = zeros(tileRows, tileCols); */
        if (1 + i == imageTiled->sizeX[0]) {
          i0 = g->sizeX[2];
          i1 = r23->sizeX[0];
          r23->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r23, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r23->data[i0] = 1 + i0;
          }

          i0 = g->sizeX[3];
          i1 = r24->sizeX[0];
          r24->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r24, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r24->data[i0] = 1 + i0;
          }

          nx = r23->sizeX[0] * r24->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = gd->sizeX[0] * gd->sizeX[1];
          gd->sizeX[0] = sz[0];
          gd->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)gd, i0, (int32_T)sizeof(real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = g->sizeX[2];
            gd->data[k] = g->data[((i + g->sizeX[0] * j) + g->sizeX[0] * g->sizeX[1]
              * (k % i0)) + g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * (k / i0)];
          }
        } else {
          i0 = g->sizeX[2];
          i1 = r21->sizeX[0];
          r21->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r21, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r21->data[i0] = 1 + i0;
          }

          i0 = g->sizeX[3];
          i1 = r22->sizeX[0];
          r22->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r22, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r22->data[i0] = 1 + i0;
          }

          nx = r21->sizeX[0] * r22->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = gd->sizeX[0] * gd->sizeX[1];
          gd->sizeX[0] = sz[0];
          gd->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)gd, i0, (int32_T)sizeof(real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = g->sizeX[2];
            gd->data[k] = g->data[(((i + g->sizeX[0] * j) + g->sizeX[0] * g->sizeX
              [1] * (k % i0)) + g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * (k / i0))
              + 1];
          }
        }

        /*  gl = zeros(tileRows, tileCols); */
        if (1 + j == imageTiled->sizeX[1]) {
          i0 = g->sizeX[2];
          i1 = r27->sizeX[0];
          r27->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r27, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r27->data[i0] = 1 + i0;
          }

          i0 = g->sizeX[3];
          i1 = r28->sizeX[0];
          r28->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r28, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r28->data[i0] = 1 + i0;
          }

          nx = r27->sizeX[0] * r28->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = gl->sizeX[0] * gl->sizeX[1];
          gl->sizeX[0] = sz[0];
          gl->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)gl, i0, (int32_T)sizeof(real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = g->sizeX[2];
            gl->data[k] = g->data[((i + g->sizeX[0] * j) + g->sizeX[0] * g->sizeX[1]
              * (k % i0)) + g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * (k / i0)];
          }
        } else {
          i0 = g->sizeX[2];
          i1 = r25->sizeX[0];
          r25->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r25, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r25->data[i0] = 1 + i0;
          }

          i0 = g->sizeX[3];
          i1 = r26->sizeX[0];
          r26->sizeX[0] = i0;
          emxEnsureCapacity((emxArray__common *)r26, i1, (int32_T)sizeof(int32_T));
          loop_ub = i0 - 1;
          for (i0 = 0; i0 <= loop_ub; i0++) {
            r26->data[i0] = 1 + i0;
          }

          nx = r25->sizeX[0] * r26->sizeX[0];
          for (i0 = 0; i0 < 2; i0++) {
            sz[i0] = 0;
          }

          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[0] = i0;
          d0 = rt_roundd_snf(blockSize);
          if (d0 < 2.147483648E+9) {
            if (d0 >= -2.147483648E+9) {
              i0 = (int32_T)d0;
            } else {
              i0 = MIN_int32_T;
            }
          } else if (d0 >= 2.147483648E+9) {
            i0 = MAX_int32_T;
          } else {
            i0 = 0;
          }

          sz[1] = i0;
          i0 = gl->sizeX[0] * gl->sizeX[1];
          gl->sizeX[0] = sz[0];
          gl->sizeX[1] = sz[1];
          emxEnsureCapacity((emxArray__common *)gl, i0, (int32_T)sizeof(real_T));
          for (k = 0; k + 1 <= nx; k++) {
            i0 = g->sizeX[2];
            gl->data[k] = g->data[((i + g->sizeX[0] * (j + 1)) + g->sizeX[0] *
              g->sizeX[1] * (k % i0)) + g->sizeX[0] * g->sizeX[1] * g->sizeX[2] * (k
              / i0)];
          }
        }

        nx = ulast->sizeX[2];
        k = ulast->sizeX[3];
        nx *= k;
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = u_ij->sizeX[0] * u_ij->sizeX[1];
        u_ij->sizeX[0] = sz[0];
        u_ij->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)u_ij, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = ulast->sizeX[2];
          i1 = ulast->sizeX[3];
          i2 = b_ulast->sizeX[0] * b_ulast->sizeX[1] * b_ulast->sizeX[2] *
            b_ulast->sizeX[3];
          b_ulast->sizeX[0] = 1;
          b_ulast->sizeX[1] = 1;
          b_ulast->sizeX[2] = i0;
          b_ulast->sizeX[3] = i1;
          emxEnsureCapacity((emxArray__common *)b_ulast, i2, (int32_T)sizeof
                            (real_T));
          loop_ub = i1 - 1;
          for (i1 = 0; i1 <= loop_ub; i1++) {
            b_loop_ub = i0 - 1;
            for (i2 = 0; i2 <= b_loop_ub; i2++) {
              b_ulast->data[b_ulast->sizeX[0] * b_ulast->sizeX[1] * i2 +
                b_ulast->sizeX[0] * b_ulast->sizeX[1] * b_ulast->sizeX[2] * i1] =
                ulast->data[((i + ulast->sizeX[0] * j) + ulast->sizeX[0] *
                             ulast->sizeX[1] * i2) + ulast->sizeX[0] * ulast->
                sizeX[1] * ulast->sizeX[2] * i1];
            }
          }

          u_ij->data[k] = b_ulast->data[k];
        }

        nx = imageTiled->sizeX[2];
        k = imageTiled->sizeX[3];
        nx *= k;
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = img_ij->sizeX[0] * img_ij->sizeX[1];
        img_ij->sizeX[0] = sz[0];
        img_ij->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)img_ij, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = imageTiled->sizeX[2];
          i1 = imageTiled->sizeX[3];
          i2 = b_imageTiled->sizeX[0] * b_imageTiled->sizeX[1] *
            b_imageTiled->sizeX[2] * b_imageTiled->sizeX[3];
          b_imageTiled->sizeX[0] = 1;
          b_imageTiled->sizeX[1] = 1;
          b_imageTiled->sizeX[2] = i0;
          b_imageTiled->sizeX[3] = i1;
          emxEnsureCapacity((emxArray__common *)b_imageTiled, i2, (int32_T)
                            sizeof(real_T));
          loop_ub = i1 - 1;
          for (i1 = 0; i1 <= loop_ub; i1++) {
            b_loop_ub = i0 - 1;
            for (i2 = 0; i2 <= b_loop_ub; i2++) {
              b_imageTiled->data[b_imageTiled->sizeX[0] * b_imageTiled->sizeX[1] *
                i2 + b_imageTiled->sizeX[0] * b_imageTiled->sizeX[1] *
                b_imageTiled->sizeX[2] * i1] = imageTiled->data[((i +
                imageTiled->sizeX[0] * j) + imageTiled->sizeX[0] *
                imageTiled->sizeX[1] * i2) + imageTiled->sizeX[0] *
                imageTiled->sizeX[1] * imageTiled->sizeX[2] * i1];
            }
          }

          img_ij->data[k] = b_imageTiled->data[k];
        }

        i0 = r->sizeX[2];
        i1 = r29->sizeX[0];
        r29->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r29, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r29->data[i0] = 1 + i0;
        }

        i0 = r->sizeX[3];
        i1 = r30->sizeX[0];
        r30->sizeX[0] = i0;
        emxEnsureCapacity((emxArray__common *)r30, i1, (int32_T)sizeof(int32_T));
        loop_ub = i0 - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          r30->data[i0] = 1 + i0;
        }

        nx = r29->sizeX[0] * r30->sizeX[0];
        for (i0 = 0; i0 < 2; i0++) {
          sz[i0] = 0;
        }

        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[0] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        sz[1] = i0;
        i0 = r_ij->sizeX[0] * r_ij->sizeX[1];
        r_ij->sizeX[0] = sz[0];
        r_ij->sizeX[1] = sz[1];
        emxEnsureCapacity((emxArray__common *)r_ij, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          i0 = r->sizeX[2];
          r_ij->data[k] = r->data[((i + r->sizeX[0] * j) + r->sizeX[0] * r->sizeX[1]
            * (k % i0)) + r->sizeX[0] * r->sizeX[1] * r->sizeX[2] * (k / i0)];
        }

        i0 = e_ug_cur->sizeX[0] * e_ug_cur->sizeX[1];
        e_ug_cur->sizeX[0] = ug_cur->sizeX[0];
        e_ug_cur->sizeX[1] = ug_cur->sizeX[1];
        emxEnsureCapacity((emxArray__common *)e_ug_cur, i0, (int32_T)sizeof
                          (real_T));
        loop_ub = ug_cur->sizeX[0] * ug_cur->sizeX[1] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          e_ug_cur->data[i0] = ug_cur->data[i0];
        }

        uStep(1.0 + (real_T)i, 1.0 + (real_T)j, blockSize, (real_T)
              imageTiled->sizeX[0], (real_T)imageTiled->sizeX[1], e_ug_cur, ug_top,
              ug_rig, ug_dow, ug_lef, gt, gr, gd, gl, u_ij, img_ij, r_ij,
              b_gamma, ug_cur);
        nx = ug_cur->sizeX[0] * ug_cur->sizeX[1];
        for (i0 = 0; i0 < 4; i0++) {
          b_sz[i0] = 0;
        }

        b_sz[0] = 1;
        b_sz[1] = 1;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        b_sz[2] = i0;
        d0 = rt_roundd_snf(blockSize);
        if (d0 < 2.147483648E+9) {
          if (d0 >= -2.147483648E+9) {
            i0 = (int32_T)d0;
          } else {
            i0 = MIN_int32_T;
          }
        } else if (d0 >= 2.147483648E+9) {
          i0 = MAX_int32_T;
        } else {
          i0 = 0;
        }

        b_sz[3] = i0;
        i0 = r2->sizeX[0] * r2->sizeX[1] * r2->sizeX[2] * r2->sizeX[3];
        r2->sizeX[0] = 1;
        r2->sizeX[1] = 1;
        r2->sizeX[2] = b_sz[2];
        r2->sizeX[3] = b_sz[3];
        emxEnsureCapacity((emxArray__common *)r2, i0, (int32_T)sizeof(real_T));
        for (k = 0; k + 1 <= nx; k++) {
          r2->data[k] = ug_cur->data[k];
        }

        loop_ub = r2->sizeX[3] - 1;
        for (i0 = 0; i0 <= loop_ub; i0++) {
          b_loop_ub = r2->sizeX[2] - 1;
          for (i1 = 0; i1 <= b_loop_ub; i1++) {
            u->data[((i + u->sizeX[0] * j) + u->sizeX[0] * u->sizeX[1] * i1) +
              u->sizeX[0] * u->sizeX[1] * u->sizeX[2] * i0] = r2->data[r2->sizeX[0] *
              r2->sizeX[1] * i1 + r2->sizeX[0] * r2->sizeX[1] * r2->sizeX[2] * i0];
          }
        }
      }
    }
  }

  emxFree_real_T(&i_u);
  emxFree_real_T(&h_u);
  emxFree_real_T(&g_u);
  emxFree_real_T(&f_u);
  emxFree_real_T(&e_u);
  emxFree_real_T(&d_u);
  emxFree_int32_T(&r40);
  emxFree_int32_T(&r39);
  emxFree_int32_T(&r38);
  emxFree_int32_T(&r37);
  emxFree_int32_T(&r36);
  emxFree_int32_T(&r35);
  emxFree_int32_T(&r34);
  emxFree_int32_T(&r33);
  emxFree_real_T(&c_u);
  emxFree_real_T(&c_imageTiled);
  emxFree_real_T(&b_u);
  emxFree_int32_T(&r32);
  emxFree_int32_T(&r31);
  emxFree_real_T(&b_ulast);
  emxFree_real_T(&b_imageTiled);
  emxFree_int32_T(&r30);
  emxFree_int32_T(&r29);
  emxFree_int32_T(&r28);
  emxFree_int32_T(&r27);
  emxFree_int32_T(&r26);
  emxFree_int32_T(&r25);
  emxFree_int32_T(&r24);
  emxFree_int32_T(&r23);
  emxFree_int32_T(&r22);
  emxFree_int32_T(&r21);
  emxFree_int32_T(&r20);
  emxFree_int32_T(&r19);
  emxFree_int32_T(&r18);
  emxFree_int32_T(&r17);
  emxFree_int32_T(&r16);
  emxFree_int32_T(&r15);
  emxFree_int32_T(&r14);
  emxFree_int32_T(&r13);
  emxFree_int32_T(&r12);
  emxFree_int32_T(&r11);
  emxFree_int32_T(&r10);
  emxFree_int32_T(&r9);
  emxFree_int32_T(&r8);
  emxFree_int32_T(&r7);
  emxFree_int32_T(&r6);
  emxFree_int32_T(&r5);
  emxFree_int32_T(&r4);
  emxFree_int32_T(&r3);
  emxFree_real_T(&e_ug_cur);
  emxFree_real_T(&d_ug_cur);
  emxFree_real_T(&c_ug_cur);
  emxFree_real_T(&b_ug_dow);
  emxFree_real_T(&b_ug_rig);
  emxFree_real_T(&b_ug_top);
  emxFree_real_T(&b_ug_cur);
  emxFree_real_T(&r2);
  emxFree_int32_T(&r1);
  emxFree_int32_T(&r0);
  emxFree_real_T(&r_ij);
  emxFree_real_T(&gl);
  emxFree_real_T(&gd);
  emxFree_real_T(&gr);
  emxFree_real_T(&gt);
  emxFree_real_T(&ug_lef);
  emxFree_real_T(&ug_dow);
  emxFree_real_T(&ug_rig);
  emxFree_real_T(&ug_top);
  emxFree_real_T(&ug_cur);
  emxFree_real_T(&img_ij);
  emxFree_real_T(&u_ij);
  emxFree_real_T(&ulast);
  emxFree_real_T(&ug);
  emxFree_real_T(&r);
  emxFree_real_T(&g);
  emxFree_real_T(&ul);
  emxFree_real_T(&ud);
  emxFree_real_T(&ur);
  emxFree_real_T(&ut);
}

/* End of code generation (ricianDenoiseTiled.c) */
