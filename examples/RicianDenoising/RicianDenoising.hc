#include "RicianDenoising.h"
#include "RicianDenoising_itemInfo.h"

struct timeval a, b;

#pragma hc continuable
void RicianDenoising_init(RicianDenoisingArgs *args, RicianDenoisingCtx *ctx) {

    int blockSize = ctx->blockSize;

    { // Put data
        s64 _i, _j;
        for (_i = 1; _i < ctx->numTileRows+1; _i++) {
            for (_j = 1; _j < ctx->numTileCols+1; _j++) {
                emxArray_real_T *loopBlock = createImageBlock(blockSize, ctx);
                // randomly initialize data, we do not care about column major order here
                real_T *loopData = loopBlock->data;
                int k;
                for (k = 0; k < blockSize * blockSize; k++) {
                    loopData[k] = user_RicianDenoising_Application_rand(0, 1);
                }
                cncPut_uData(loopBlock, 0, _i, _j, ctx);
                cncPut_imageData(loopBlock, _i, _j, ctx);
            }
        }
    }

    // start computation
    gettimeofday(&a, 0);

    { // Prescribe steps
        s64 _iter, _i, _j;
        for (_iter = 1; _iter < ctx->iters+1; _iter++) {
            for (_i = 1; _i < ctx->numTileRows+1; _i++) {
                for (_j = 1; _j < ctx->numTileCols+1; _j++) {
                    cncPrescribe_uDiffCompute(_iter, _i, _j, ctx);
                    cncPrescribe_gCompute(_iter, _i, _j, ctx);
                    cncPrescribe_rCompute(_iter, _i, _j, ctx);
                    cncPrescribe_ugCompute(_iter, _i, _j, ctx);
                    cncPrescribe_uCompute(_iter, _i, _j, ctx);
                }
            }
        }
    }

    // Set finalizer function's tag
    RicianDenoising_await(ctx);

}


/*
 * typeof doneFlag is int 
 */
#pragma hc continuable
void RicianDenoising_finalize(doneFlagItem *doneFlag, RicianDenoisingCtx *ctx) {
    gettimeofday(&b, 0);
    double secs = ((b.tv_sec - a.tv_sec)*1000000 + (b.tv_usec - a.tv_usec))/1000000.0;
    printf("The computation took %f seconds\n", secs);
}

void *cncItemSanitizeFn_imageData(void *payload) {
    // Read parameters
    emxArray_real_T *dataStruct = payload;
    int numEntries = dataStruct->allocatedSize;
    real_T *matrix = (real_T*)(dataStruct+1);
    int32_T *dims = (int32_T*)(matrix+numEntries);
    // Update pointers
    dataStruct->data = matrix;
    dataStruct->sizeX = dims;
    return dataStruct;
}

emxArray_real_T *createImageBlock(int sideDim, RicianDenoisingCtx *ctx) {
    size_t byteCount = cncItemSize_imageData(ctx);
    emxArray_real_T *block = hc_malloc(byteCount);
    block->numDimensions = 2;
    block->allocatedSize = sideDim * sideDim;
    cncItemSanitizeFn_imageData(block);
    block->sizeX[0] = sideDim;
    block->sizeX[1] = sideDim;
    block->canFreeData = TRUE;
    return block;
}

