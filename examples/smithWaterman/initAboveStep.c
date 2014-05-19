
#include "Common.h"

void initAboveStep(int tw, int ntw, Context *context){
    int j, jj;
    int *above;
    for(j = 0; j < ntw; j++){
        cncHandle_t above_handle = cncCreateItem_above(&above, tw+1);
        for (jj=0; jj <= tw; jj++) {
            // TODO - Why isn't this just 0?
            above[jj] = GAP_PENALTY*(j*tw+jj);
        }
        cncPut_above(above_handle, 0, j, context);
    }
}

