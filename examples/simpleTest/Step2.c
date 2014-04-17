
#include "Common.h"
void Step2(int k, int* Bi0, ocrEdtDep_t deps[], Context* context){
	printf("Step2 %d\n", k);
	int* Ci1;
	ocrGuid_t Ci1_guid;
	ocrDbCreate(&Ci1_guid, (void **) &Ci1, sizeof(int), 0xdead, NULL_GUID, NO_ALLOC);
	Ci1[0] = Bi0[0] * 2;

	char* tagCi1 = createTag(1, k);
	Put(Ci1_guid, tagCi1, context->Ci);
	printf("Step2 done putting item %d with tag %s\n", Ci1[0], tagCi1);
}


