
#include "Common.h"
void kjComputeStep( int k, int numTiles0, Context* context){
	int _index1_1;
	for(_index1_1 = k+1; _index1_1 < numTiles0; _index1_1++){
		char* tagcontrolS2Tag1 = createTag(2, k, _index1_1);
		prescribeStep("kjiComputeStep", tagcontrolS2Tag1, context);
		prescribeStep("s2ComputeStep", tagcontrolS2Tag1, context);
	}
}


