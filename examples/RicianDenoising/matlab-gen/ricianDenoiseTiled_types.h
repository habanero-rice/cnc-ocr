/*
 * ricianDenoiseTiled_types.h
 *
 * Code generation for function 'ricianDenoiseTiled'
 *
 * C source code generated on: Thu Oct 11 23:26:05 2012
 *
 */

#ifndef __RICIANDENOISETILED_TYPES_H__
#define __RICIANDENOISETILED_TYPES_H__

/* Type Definitions */
#ifndef struct_emxArray__common
#define struct_emxArray__common
typedef struct emxArray__common
{
    void *data;
    int32_T *sizeX;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray__common;
#endif
#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T
typedef struct emxArray_int32_T
{
    int32_T *data;
    int32_T *sizeX;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray_int32_T;
#endif
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
typedef struct emxArray_real_T
{
    real_T *data;
    int32_T *sizeX;
    int32_T allocatedSize;
    int32_T numDimensions;
    boolean_T canFreeData;
} emxArray_real_T;
#endif

#endif
/* End of code generation (ricianDenoiseTiled_types.h) */
