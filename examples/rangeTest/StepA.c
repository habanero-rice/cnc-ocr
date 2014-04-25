
#include "Common.h"
void StepA( int i, int j, CollAItem* CollA0, Context* context){
    int x;
    int total = 0;
    for (x=i; x<j; x++) {
        total += *CollA0[x].item;
    }

    int* TotalA1;
    ocrGuid_t TotalA1_guid;
    ocrDbCreate(&TotalA1_guid, (void **) &TotalA1, sizeof(int), 0xdead, NULL_GUID, NO_ALLOC);
    *TotalA1 = total;
    char* tagTotalA1 = CREATE_TAG(i, j);
    Put(TotalA1_guid, tagTotalA1, context->TotalA);
}
