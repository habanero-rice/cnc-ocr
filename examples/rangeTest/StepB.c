
#include "Common.h"
void StepB( int i, int j, CollBItem* CollB0, Context* context){
    int x;
    int total = 0;
    for (x=i; x<j; x++) {
        total += CollB0[x].item;
    }

    int* TotalB1;
    TotalB1 = (int* ) malloc ( 1 * sizeof (int) );

    ocrGuid_t TotalB1_guid;
    ocrDbCreate(&TotalB1_guid, (void **) &TotalB1, sizeof(int), 0xdead, NULL_GUID, NO_ALLOC);
    char* tagTotalB1 = CREATE_TAG(i, j);
    *TotalB1 = total;
    Put(TotalB1_guid, tagTotalB1, context->TotalB);
}


