
#include "Dispatch.h"

void cncEnvIn(int argc, char **argv, Context *context) {
    // Sum from 0 until 10
    int x = 0, y = 10;

    int i;
    int *CollA[100];
    int *CollB[100];

    for(i = 0; i < 100; i++){
        cncHandle_t CollA_handle = cncCreateItem_CollA(&CollA[i]);
        *CollA[i] = i;
        char *tagCollA = CREATE_TAG(i);
        Put(CollA_handle, tagCollA, context->CollA);
    }

    for(i = 0; i < 100; i++){
        cncHandle_t CollB_handle = cncCreateItem_CollB(&CollB[i]);
        *CollB[i] = i;
        char *tagCollB = CREATE_TAG(i);
        Put(CollB_handle, tagCollB, context->CollB);
    }

    char *tagSATag2 = CREATE_TAG(x, y);
    prescribeStep("StepA", tagSATag2, context);

    char *tagSBTag3 = CREATE_TAG(x, y);
    prescribeStep("StepB", tagSBTag3, context);

    char *tagOut = CREATE_TAG(x, y);
    setEnvOutTag(tagOut, context);
}

void cncEnvOut(int x, int y, TotalAItem TotalA, TotalBItem TotalB, Context* context) {
    PRINTF("Total A [%d, %d): %d\n", x, y, *TotalA.item);
    PRINTF("Total B [%d, %d): %d\n", x, y, TotalB.item);
}
