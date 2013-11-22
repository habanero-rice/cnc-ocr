
#include "Common.h"
void Step1( int k, int* Ai0, Context* context){
	printf("Step1 %d\n", k);
	int* Bi1;
	ocrGuid_t Bi1_guid;
	ocrDbCreate(&Bi1_guid, (void **) &Bi1, sizeof(int), 0xdead, NULL_GUID, NO_ALLOC);
	*Bi1 = *Ai0 + 1;

	char* tagBi1 = createTag(1, k);
	Put(Bi1_guid, tagBi1, context->Bi);

	char* tagS2Tag2 = createTag(1, k);
	prescribeStep("Step2", tagS2Tag2, context);

}


