
   /***** AUTO-GENERATED FILE from file RangeTest.cnc - only generated if file does not exist (on running cncc_t the first time) - feel free to edit *****/

#include "Dispatch.h"
#include <string.h>

ocrGuid_t finishEdt(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){
	Context* context = initGraph();

	// Seed CollA with integers 0 until 100
	int _index1_0;
	for(_index1_0 = 0; _index1_0 < 100 - 0; _index1_0++){
		int *CollA1;
		ocrGuid_t CollA1_guid;
		ocrDbCreate(&CollA1_guid, (void **) &CollA1, sizeof(int), 0xdead, NULL_GUID, NO_ALLOC);
		*CollA1 = _index1_0;
		char* tagCollA1 = createTag(1, _index1_0 + 0);
		Put(CollA1_guid, tagCollA1, context->CollA);
	}

	// Seed CollB with integers 0 until 100
	int _index0_0;
	for(_index0_0 = 0; _index0_0 < 100 - 0; _index0_0++){
		int *CollB0;
		ocrGuid_t CollB0_guid;
		ocrDbCreate(&CollB0_guid, (void **) &CollB0, sizeof(int), 0xdead, NULL_GUID, NO_ALLOC);
		*CollB0 = _index0_0;
		char* tagCollB0 = createTag(1, _index0_0 + 0);
		Put(CollB0_guid, tagCollB0, context->CollB);
	}

	// Sum the entries in CollA 0 until 10
	char *tagA = CREATE_TAG(0, 10);
	prescribeStep("StepA", tagA, context);

	// Sum the entries in CollB 0 until 10
	char *tagB = CREATE_TAG(0, 10);
	prescribeStep("StepB", tagB, context);

	deleteGraph(context);
}

ocrGuid_t shutdownEdt(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){
	ocrShutdown();
}

ocrGuid_t mainEdt(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]){
	ocrGuid_t edt_guid, templ_guid, out_guid;
	ocrEdtTemplateCreate(&templ_guid, finishEdt, 0, 1);
	ocrEdtCreate(&edt_guid, templ_guid,
		/*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
		/*depc=*/EDT_PARAM_DEF, /*depv=*/NULL,
		/*properties=*/0, /*affinity=*/NULL_GUID, /*outEvent=*/&out_guid);

	{
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, shutdownEdt, 0, 1);
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/EDT_PARAM_DEF, /*paramv=*/NULL,
			/*depc=*/EDT_PARAM_DEF, /*depv=*/&out_guid,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL);
	}

	ocrAddDependence(NULL_GUID, edt_guid, 0, DB_DEFAULT_MODE);
}

