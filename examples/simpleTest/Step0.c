
#include "Common.h"
void Step0(int k, sizeItem size0, Context* context){
	PRINTF("Step0 %d\n", k);
	int _index1_0;
	for(_index1_0 = 0; _index1_0 < size0.item; _index1_0++){
		char* tagS1Tag1 = CREATE_TAG(_index1_0);
		prescribeStep("Step1", tagS1Tag1, context);
	}
}


