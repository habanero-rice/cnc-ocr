
#include "Common.h"
#include <limits.h>

void initLeftStep(int th, int nth, Context *context) {
    int i, ii;
    int *left;
    for(i = 0; i < nth; i++){
        cncHandle_t left_handle = cncCreateItem_left(&left, th+1);
        for (ii=0; ii <= th; ii++) {
            // TODO - Why isn't this just 0?
            left[ii] = GAP_PENALTY*(i*th+ii);
        }
        Put(left_handle, CREATE_TAG(i, 0), context->left);
    }
}

