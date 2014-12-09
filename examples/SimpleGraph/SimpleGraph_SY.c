#include "SimpleGraph.h"

/* Put an item to the Y collection */
void SY(cncTag_t y, SimpleGraphCtx *ctx) {
    int *Y = cncCreateItem_Y();
    *Y = y;
    cncPut_Y(Y, ctx);
}
