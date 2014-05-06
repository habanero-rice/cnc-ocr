
#include "Common.h"
void kjiComputeStep(int k, int j, Context *context) {
    int i;
    for(i = k+1; i < j+1; i++){
        char *tagcontrolS3Tag0 = CREATE_TAG(k, j, i);
        CNC_PRESCRIBE(s3ComputeStep, tagcontrolS3Tag0, context);
    }
}


