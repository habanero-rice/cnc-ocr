
#include "Common.h"
void kjComputeStep(int k, numTilesItem numTiles, Context *context) {
    int j;
    for(j = k+1; j < numTiles.item; j++){
        cncPrescribe_kjiComputeStep(k, j, context);
        cncPrescribe_s2ComputeStep(k, j, context);
    }
}


