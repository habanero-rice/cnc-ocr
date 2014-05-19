
#include "Common.h"

void Step1(int k, AiItem Ai, Context *context){
	PRINTF("Step1 %d\n", k);

	int *Bi;
	cncHandle_t Bi_handle = cncCreateItem_Bi(&Bi, 1);
	*Bi = *Ai.item + 1;
	cncPut_Bi(Bi_handle, k, context);

	cncPrescribe_Step2(k, context);
}

