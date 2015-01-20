#include "SmithWaterman.h"

static inline int cncItemSize_above(SmithWatermanCtx *ctx) {
    return sizeof(int) * (ctx->tw+1);
}
static inline int cncItemSize_left(SmithWatermanCtx *ctx) {
    return sizeof(int) * (ctx->th+1);
}
static inline int cncItemSize_data(SmithWatermanCtx *ctx) {
    return ctx->dataSize;
}
static inline int cncItemSize_startTime(SmithWatermanCtx *ctx) {
    return sizeof(struct timeval);
}

