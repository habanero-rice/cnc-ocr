
#include "Common.h"
void kComputeStep(int k, numTilesItem numTiles, Context *context) {
	int _index1_0;
	for(_index1_0 = 0; _index1_0 < numTiles.item; _index1_0++){
		char *tagcontrolS1Tag1 = CREATE_TAG(_index1_0);
		prescribeStep("kjComputeStep", tagcontrolS1Tag1, context);
		prescribeStep("s1ComputeStep", tagcontrolS1Tag1, context);
	}
}


