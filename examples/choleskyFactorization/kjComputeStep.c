
#include "Common.h"
void kjComputeStep(int k, numTilesItem numTiles, Context *context) {
	int _index1_1;
	for(_index1_1 = k+1; _index1_1 < numTiles.item; _index1_1++){
		char *tagcontrolS2Tag1 = CREATE_TAG(k, _index1_1);
		prescribeStep("kjiComputeStep", tagcontrolS2Tag1, context);
		prescribeStep("s2ComputeStep", tagcontrolS2Tag1, context);
	}
}


