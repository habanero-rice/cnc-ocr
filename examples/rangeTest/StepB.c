
#include "Common.h"

void StepB(int i, int j, CollBItem *CollB, Context *context) {
    int x;
    int total = 0;
    for (x=i; x<j; x++) {
        total += CollB[x].item;
    }

    int *TotalB;
    cncHandle_t TotalB_handle = cncCreateItem_TotalB(&TotalB);
    *TotalB = total;

    char *tagTotalB = CREATE_TAG(i, j);
    Put(TotalB_handle, tagTotalB, context->TotalB);
}


