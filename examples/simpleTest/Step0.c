
#include "Common.h"

void Step0(int k, sizeItem size0, Context *context) {
	PRINTF("Step0 %d\n", k);

	int i;
	for (i = 0; i < size0.item; i++) {
		cncPrescribe_Step1(i, context);
	}
}

