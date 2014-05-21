
#include "Context.h"

void cncEnvIn(int argc, char **argv, Context *context) {
    // Sum from 0 until 10
    int x = 0, y = 10;

    int i;
    int *CollA[100];
    int *CollB[100];

    for(i = 0; i < 100; i++){
        cncHandle_t CollA_handle = cncCreateItem_CollA(&CollA[i], 1);
        *CollA[i] = i;
        cncPut_CollA(CollA_handle, i, context);
    }

    for(i = 0; i < 100; i++){
        cncHandle_t CollB_handle = cncCreateItem_CollB(&CollB[i]);
        *CollB[i] = i;
        cncPut_CollB(CollB_handle, i, context);
    }

    cncPrescribe_StepA(x, y, context);
    cncPrescribe_StepB(x, y, context);
    cncPrescribe_cncEnvOut(x, y, context);
}

void cncEnvOut(int x, int y, TotalAItem TotalA, TotalBItem TotalB, Context* context) {
    PRINTF("Total A [%d, %d): %d\n", x, y, *TotalA.item);
    PRINTF("Total B [%d, %d): %d\n", x, y, TotalB.item);
}
