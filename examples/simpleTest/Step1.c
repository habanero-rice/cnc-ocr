
#include "Common.h"

void Step1(int k, AiItem Ai, Context *context){
	PRINTF("Step1 %d\n", k);

	int *Bi;
	cncHandle_t Bi_handle = cncCreateItem_Bi(&Bi);
	*Bi = *Ai.item + 1;

	char *tagBi = CREATE_TAG(k);
	Put(Bi_handle, tagBi, context->Bi);

	char *tagS2Tag2 = CREATE_TAG(k);
	prescribeStep("Step2", tagS2Tag2, context);

}

