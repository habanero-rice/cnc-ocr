
#include "Common.h"
void Step2(int k, BiItem Bi0, Context* context){
	PRINTF("Step2 %d\n", k);
	int* Ci1;
	ocrGuid_t Ci1_guid;
	ocrDbCreate(&Ci1_guid, (void **) &Ci1, sizeof(int), 0, NULL_GUID, NO_ALLOC);
	Ci1[0] = Bi0.item[0] * 2;

	char* tagCi1 = CREATE_TAG(k);
	Put(Ci1_guid, tagCi1, context->Ci);
	PRINTF("Step2 done putting item %d with tag %s\n", Ci1[0], tagCi1);
}


