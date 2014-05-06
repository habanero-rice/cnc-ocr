
#include "Common.h"
void kComputeStep(int k, numTilesItem numTiles, Context *context) {
    for(k = 0; k < numTiles.item; k++){
        char *tagcontrolS1Tag1 = CREATE_TAG(k);
        CNC_PRESCRIBE(kjComputeStep, tagcontrolS1Tag1, context);
        CNC_PRESCRIBE(s1ComputeStep, tagcontrolS1Tag1, context);
    }
}


