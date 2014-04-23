
#include "Common.h"
void StepA( int i, int j, CollAItem CollA0[], Context* context){
    int x;
    int total = 0;
    for (x=i; x<j; x++) {
        total += *CollA0[x].item;
    }
    PRINTF("Total A: %d\n", total);
}


