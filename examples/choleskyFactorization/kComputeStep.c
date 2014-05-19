
#include "Common.h"
void kComputeStep(int k, numTilesItem numTiles, Context *context) {
    for(k = 0; k < numTiles.item; k++){
        cncPrescribe_kjComputeStep(k, context);
        cncPrescribe_s1ComputeStep(k, context);
    }
}


