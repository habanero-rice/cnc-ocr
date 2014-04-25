
#include "Common.h"

void StepA(int i, int j, CollAItem *CollA, Context *context) {
    int x;
    int total = 0;
    for (x=i; x<j; x++) {
        total += *CollA[x].item;
    }

    int *TotalA;
    cncHandle_t TotalA_handle = cncCreateItem_TotalA(&TotalA);
    *TotalA = total;

    char *tagTotalA = CREATE_TAG(i, j);
    Put(TotalA_handle, tagTotalA, context->TotalA);
}
