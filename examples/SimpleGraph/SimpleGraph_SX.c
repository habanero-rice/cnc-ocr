#include "SimpleGraph.h"

/* Put an item to the X collection */
void SX(cncTag_t x, SimpleGraphCtx *ctx) {
    int *X;
    cncHandle_t XHandle = cncCreateItem_X(&X);
    *X = x;
    cncPut_X(XHandle, ctx);
}
