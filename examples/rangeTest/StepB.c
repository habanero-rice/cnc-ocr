
#include "Common.h"
void StepB( int i, int j, CollBItem CollB0[], Context* context){
    int x;
    int total = 0;
    for (x=i; x<j; x++) {
        total += CollB0[x].item;
    }
    PRINTF("Total B: %d\n", total);
}


