
#include "Common.h"

void Step2(int k, BiItem Bi, Context *context) {
	PRINTF("Step2 %d\n", k);

	int *Ci;
	cncHandle_t Ci_handle = cncCreateItem_Ci(&Ci, 1);
	*Ci = *Bi.item * 2;

	char *tagCi = CREATE_TAG(k);
	Put(Ci_handle, tagCi, context->Ci);

	PRINTF("Step2 done putting item %d with tag %s\n", *Ci, tagCi);
}


