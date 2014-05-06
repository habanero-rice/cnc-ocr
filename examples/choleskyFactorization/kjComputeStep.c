
#include "Common.h"
void kjComputeStep(int k, numTilesItem numTiles, Context *context) {
    int j;
    for(j = k+1; j < numTiles.item; j++){
        char *tagcontrolS2Tag1 = CREATE_TAG(k, j);
        CNC_PRESCRIBE(kjiComputeStep, tagcontrolS2Tag1, context);
        CNC_PRESCRIBE(s2ComputeStep, tagcontrolS2Tag1, context);
    }
}


