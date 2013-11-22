
	/***** AUTO-GENERATED FILE. Do not modify unless tag functions are missing and the code generated as suggestion is in comment. *****/
	/***** WARNING: this file WILL BE OVERWRITTEN on each call of cncc_t Cholesky.cnc *****/

#ifndef _COMMON_H
#define _COMMON_H
#include "Dispatch.h"

void kComputeStep( int k, int numTiles0, Context* context );
void s2ComputeStep( int k, int j, double** Lkji0, double** Lkji1, int tileSize2, Context* context );
void kjComputeStep( int k, int numTiles0, Context* context );
void s3ComputeStep( int k, int j, int i, double** Lkji0, double** Lkji1, double** Lkji2, int tileSize3, Context* context );
void kjiComputeStep( int k, int j, Context* context );
void s1ComputeStep( int k, double** Lkji0, int tileSize1, Context* context );
#endif /*_COMMON_H */
