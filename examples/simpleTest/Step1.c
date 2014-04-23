
#include "Common.h"
void Step1(int k, AiItem Ai0, Context* context){
	PRINTF("Step1 %d\n", k);
	int* Bi1;
	ocrGuid_t Bi1_guid;
	ocrDbCreate(&Bi1_guid, (void **) &Bi1, sizeof(int), 0, NULL_GUID, NO_ALLOC);
	*Bi1 = *Ai0.item + 1;

	char* tagBi1 = CREATE_TAG(k);
	Put(Bi1_guid, tagBi1, context->Bi);

	char* tagS2Tag2 = CREATE_TAG(k);
	prescribeStep("Step2", tagS2Tag2, context);

}


