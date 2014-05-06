
#include "Common.h"

void Step0(int k, sizeItem size0, Context *context) {
	PRINTF("Step0 %d\n", k);

	int i;
	for (i = 0; i < size0.item; i++) {
		char *tagS1Tag1 = CREATE_TAG(i);
		CNC_PRESCRIBE(Step1, tagS1Tag1, context);
	}
}


