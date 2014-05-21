
#include "Common.h"
void kjiComputeStep(int k, int j, Context *context) {
    int i;
    for(i = k+1; i < j+1; i++){
        cncPrescribe_s3ComputeStep(k, j, i, context);
    }
}


