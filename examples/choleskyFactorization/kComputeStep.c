
#include "Common.h"
void kComputeStep( int k, int numTiles0, Context* context){
	int _index1_0;
	for(_index1_0 = 0; _index1_0 < numTiles0; _index1_0++){
		char* tagcontrolS1Tag1 = createTag(1, _index1_0);
		prescribeStep("kjComputeStep", tagcontrolS1Tag1, context);
		prescribeStep("s1ComputeStep", tagcontrolS1Tag1, context);
	}
}


