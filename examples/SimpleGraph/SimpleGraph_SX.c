#include "SimpleGraph.h"

/* Put an item to the X collection */
void SX(cncTag_t x, SimpleGraphCtx *ctx) {
    int *X = cncCreateItem_X();
    *X = x;
    cncPut_X(X, ctx);
}
