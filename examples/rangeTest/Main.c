
   /***** AUTO-GENERATED FILE from file rangeTest.cnc - only generated if file does not exist (on running cncocr_t the first time) - feel free to edit *****/

#include "Dispatch.h"

void cncEnvIn(int argc, char **argv, Context *context) {
    // Sum from 0 until 10
    int x = 0, y = 10;

	int i;
	int *CollA[100];

	int *CollB[100];
	for(i = 0; i < 100; i++){
		CollB[i] = (int* ) malloc ( 1 * sizeof (int) );
	}

	for(i = 0; i < 100; i++){
		ocrGuid_t CollA_guid;
		ocrDbCreate(&CollA_guid, (void **) &CollA[i], sizeof(int), 0xdead, NULL_GUID, NO_ALLOC);
		char *tagCollA = CREATE_TAG(i);
        *CollA[i] = i;
		Put(CollA_guid, tagCollA, context->CollA);
	}

	for(i = 0; i < 100; i++){
		ocrGuid_t CollB_guid;
		ocrDbCreate(&CollB_guid, (void **) &CollB[i], sizeof(int), 0xdead, NULL_GUID, NO_ALLOC);
		char *tagCollB = CREATE_TAG(i);
        *CollB[i] = i;
		Put(CollB_guid, tagCollB, context->CollB);
	}

	char *tagSATag2 = CREATE_TAG(x, y);
	prescribeStep("StepA", tagSATag2, context);

	char *tagSBTag3 = CREATE_TAG(x, y);
	prescribeStep("StepB", tagSBTag3, context);

	char *tagOut = CREATE_TAG(x, y);
    setEnvOutTag(tagOut, context);
}

void cncEnvOut(int x, int y, TotalAItem TotalA, TotalBItem TotalB, Context* context) {
	PRINTF("Total A (%d..%d): %d\n", x, y, *TotalA.item);
	PRINTF("Total B (%d..%d): %d\n", x, y, TotalB.item);
}
