
#include "Common.h"
void Step0(int k, int size0, ocrEdtDep_t deps[], Context* context){
	printf("Step0 %d\n", k);
	int _index1_0;
	for(_index1_0 = 0; _index1_0 < size0; _index1_0++){
		char* tagS1Tag1 = createTag(1, _index1_0);
		prescribeStep("Step1", tagS1Tag1, context);
	}
}


