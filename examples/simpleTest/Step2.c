
#include "Common.h"

void Step2(int k, BiItem Bi, Context *context) {
	PRINTF("Step2 %d\n", k);

	int *Ci;
	cncHandle_t Ci_handle = cncCreateItem_Ci(&Ci, 1);
	*Ci = *Bi.item * 2;
	cncPut_Ci(Ci_handle, k, context);

	PRINTF("Step2 done putting item %d with tag %d\n", *Ci, k);
}


