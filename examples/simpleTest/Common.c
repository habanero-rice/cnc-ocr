
	/***** AUTO-GENERATED FILE. Do not modify unless tag functions are missing and the code generated as suggestion is in comment. *****/
	/***** WARNING: this file WILL BE OVERWRITTEN on each call of cncc_t simpleTest.cnc *****/

#include "Common.h"

/*
Step2 dependency adding implementation
*/

void Step2_dependencies(char * tag, ocrGuid_t edt_guid, Context * context){
	int k = getTag(tag, 0);
	int edt_index=0;
	char* tagBi0 = createTag(1, k);
	__registerConsumer( tagBi0, context->Bi, edt_guid, edt_index++);
}

/*
Step2 gets implementation
*/

ocrGuid_t Step2_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){

	Context* context = (Context*)paramv[1];
	int k = getTag((char*)paramv[0], 0);
	int edt_index=0;
	int* Bi0;
	char* tagBi0 = createTag(1, k);
	Bi0 = (int* )depv[edt_index++].ptr;
	Step2( k, Bi0, context );
	return 0;
}

/*
Step1 dependency adding implementation
*/

void Step1_dependencies(char * tag, ocrGuid_t edt_guid, Context * context){
	int k = getTag(tag, 0);
	int edt_index=0;
	char* tagAi0 = createTag(1, k);
	__registerConsumer( tagAi0, context->Ai, edt_guid, edt_index++);
}

/*
Step1 gets implementation
*/

ocrGuid_t Step1_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){

	Context* context = (Context*)paramv[1];
	int k = getTag((char*)paramv[0], 0);
	int edt_index=0;
	int* Ai0;
	char* tagAi0 = createTag(1, k);
	Ai0 = (int* )depv[edt_index++].ptr;
	Step1( k, Ai0, context );
	return 0;
}

/*
Step0 dependency adding implementation
*/

void Step0_dependencies(char * tag, ocrGuid_t edt_guid, Context * context){
	int k = getTag(tag, 0);
	int edt_index=0;
	char* tagsize0 = createTag(1, 0);
	__registerConsumer( tagsize0, context->size, edt_guid, edt_index++);
}

/*
Step0 gets implementation
*/

ocrGuid_t Step0_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){

	Context* context = (Context*)paramv[1];
	int k = getTag((char*)paramv[0], 0);
	int edt_index=0;
	int* sizetemp0;
	int size0;
	char* tagsize0 = createTag(1, 0);
	sizetemp0 = (int* )depv[edt_index++].ptr;
	size0 = sizetemp0[0];
	Step0( k, size0, context );
	return 0;
}


