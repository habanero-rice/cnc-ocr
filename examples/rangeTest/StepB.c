
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
    cncPut_TotalB(TotalB_handle, i, j, context);
}


