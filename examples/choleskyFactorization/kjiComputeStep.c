
#include "Common.h"
void kjiComputeStep( int k, int j, Context* context){
	int _index0_2;
	for(_index0_2 = k+1; _index0_2 < j+1; _index0_2++){
		char* tagcontrolS3Tag0 = createTag(3, k, j, _index0_2);
		prescribeStep("s3ComputeStep", tagcontrolS3Tag0, context);
	}
}


