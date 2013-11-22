
	/***** AUTO-GENERATED FILE. Do not modify unless tag functions are missing and the code generated as suggestion is in comment. *****/
	/***** WARNING: this file WILL BE OVERWRITTEN on each call of cncc_t Cholesky.cnc *****/

#include "Common.h"

/*
kComputeStep dependency adding implementation
*/

void kComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context){
	int k = getTag(tag, 0);
	int edt_index=0;
	char* tagnumTiles0 = createTag(1, 0);
	__registerConsumer( tagnumTiles0, context->numTiles, edt_guid, edt_index++);
}

/*
kComputeStep gets implementation
*/

ocrGuid_t kComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){

	Context* context = (Context*)paramv[1];
	int k = getTag((char*)paramv[0], 0);
	int edt_index=0;
	int* numTilestemp0;
	int numTiles0;
	char* tagnumTiles0 = createTag(1, 0);
	numTilestemp0 = (int* )depv[edt_index++].ptr;
	numTiles0 = numTilestemp0[0];
	kComputeStep( k, numTiles0, context );
	return 0;
}

/*
s2ComputeStep dependency adding implementation
*/

void s2ComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context){
	int k = getTag(tag, 0);
	int j = getTag(tag, 1);
	int edt_index=0;
	char* tagLkji0 = createTag(3, j, k, k);
	__registerConsumer( tagLkji0, context->Lkji, edt_guid, edt_index++);

	char* tagLkji1 = createTag(3, k, k, k+1);
	__registerConsumer( tagLkji1, context->Lkji, edt_guid, edt_index++);

	char* tagtileSize2 = createTag(1, 0);
	__registerConsumer( tagtileSize2, context->tileSize, edt_guid, edt_index++);
}

/*
s2ComputeStep gets implementation
*/

ocrGuid_t s2ComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){

	Context* context = (Context*)paramv[1];
	int k = getTag((char*)paramv[0], 0);
	int j = getTag((char*)paramv[0], 1);
	int edt_index=0;
	double** Lkji0;
	char* tagLkji0 = createTag(3, j, k, k);
	Lkji0 = (double** )depv[edt_index++].ptr;

	double** Lkji1;
	char* tagLkji1 = createTag(3, k, k, k+1);
	Lkji1 = (double** )depv[edt_index++].ptr;

	int* tileSizetemp2;
	int tileSize2;
	char* tagtileSize2 = createTag(1, 0);
	tileSizetemp2 = (int* )depv[edt_index++].ptr;
	tileSize2 = tileSizetemp2[0];
	s2ComputeStep( k, j, Lkji0, Lkji1, tileSize2, context );
	return 0;
}

/*
kjComputeStep dependency adding implementation
*/

void kjComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context){
	int k = getTag(tag, 0);
	int edt_index=0;
	char* tagnumTiles0 = createTag(1, 0);
	__registerConsumer( tagnumTiles0, context->numTiles, edt_guid, edt_index++);
}

/*
kjComputeStep gets implementation
*/

ocrGuid_t kjComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){

	Context* context = (Context*)paramv[1];
	int k = getTag((char*)paramv[0], 0);
	int edt_index=0;
	int* numTilestemp0;
	int numTiles0;
	char* tagnumTiles0 = createTag(1, 0);
	numTilestemp0 = (int* )depv[edt_index++].ptr;
	numTiles0 = numTilestemp0[0];
	kjComputeStep( k, numTiles0, context );
	return 0;
}

/*
s3ComputeStep dependency adding implementation
*/

void s3ComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context){
	int k = getTag(tag, 0);
	int j = getTag(tag, 1);
	int i = getTag(tag, 2);
	int edt_index=0;
	char* tagLkji0 = createTag(3, j, i, k);
	__registerConsumer( tagLkji0, context->Lkji, edt_guid, edt_index++);

	char* tagLkji1 = createTag(3, j, k, k+1);
	__registerConsumer( tagLkji1, context->Lkji, edt_guid, edt_index++);

	char* tagLkji2 = createTag(3, i, k, k+1);
	__registerConsumer( tagLkji2, context->Lkji, edt_guid, edt_index++);

	char* tagtileSize3 = createTag(1, 0);
	__registerConsumer( tagtileSize3, context->tileSize, edt_guid, edt_index++);
}

/*
s3ComputeStep gets implementation
*/

ocrGuid_t s3ComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){

	Context* context = (Context*)paramv[1];
	int k = getTag((char*)paramv[0], 0);
	int j = getTag((char*)paramv[0], 1);
	int i = getTag((char*)paramv[0], 2);
	int edt_index=0;
	double** Lkji0;
	char* tagLkji0 = createTag(3, j, i, k);
	Lkji0 = (double** )depv[edt_index++].ptr;

	double** Lkji1;
	char* tagLkji1 = createTag(3, j, k, k+1);
	Lkji1 = (double** )depv[edt_index++].ptr;

	double** Lkji2;
	char* tagLkji2 = createTag(3, i, k, k+1);
	Lkji2 = (double** )depv[edt_index++].ptr;

	int* tileSizetemp3;
	int tileSize3;
	char* tagtileSize3 = createTag(1, 0);
	tileSizetemp3 = (int* )depv[edt_index++].ptr;
	tileSize3 = tileSizetemp3[0];
	s3ComputeStep( k, j, i, Lkji0, Lkji1, Lkji2, tileSize3, context );
	return 0;
}

/*
kjiComputeStep dependency adding implementation
*/

void kjiComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context){
	int k = getTag(tag, 0);
	int j = getTag(tag, 1);
	int edt_index=0;}

/*
kjiComputeStep gets implementation
*/

ocrGuid_t kjiComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){

	Context* context = (Context*)paramv[1];
	int k = getTag((char*)paramv[0], 0);
	int j = getTag((char*)paramv[0], 1);
	int edt_index=0;	kjiComputeStep( k, j, context );
	return 0;
}

/*
s1ComputeStep dependency adding implementation
*/

void s1ComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context){
	int k = getTag(tag, 0);
	int edt_index=0;
	char* tagLkji0 = createTag(3, k, k, k);
	__registerConsumer( tagLkji0, context->Lkji, edt_guid, edt_index++);

	char* tagtileSize1 = createTag(1, 0);
	__registerConsumer( tagtileSize1, context->tileSize, edt_guid, edt_index++);
}

/*
s1ComputeStep gets implementation
*/

ocrGuid_t s1ComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){

	Context* context = (Context*)paramv[1];
	int k = getTag((char*)paramv[0], 0);
	int edt_index=0;
	double** Lkji0;
	char* tagLkji0 = createTag(3, k, k, k);
	Lkji0 = (double** )depv[edt_index++].ptr;

	int* tileSizetemp1;
	int tileSize1;
	char* tagtileSize1 = createTag(1, 0);
	tileSizetemp1 = (int* )depv[edt_index++].ptr;
	tileSize1 = tileSizetemp1[0];
	s1ComputeStep( k, Lkji0, tileSize1, context );
	return 0;
}


