#include "RicianDenoising.h"

int main(int argc, char **argv) {

    if (argc != 5) {
        fprintf(stderr, "Usage: RicianDenoising <rows> <cols> <block_size> <iters>\n");
        exit(1);
    }

    // Create a new graph ctx
    RicianDenoisingCtx *ctx = RicianDenoising_create();

    ctx->numTileRows = atoi(argv[1]);
    ctx->numTileCols = atoi(argv[2]);
    ctx->blockSize = atoi(argv[3]);
    ctx->iters = atoi(argv[4]);

fprintf(stderr, "Matrix size: %d x %d\n", ctx->numTileRows * ctx->blockSize, ctx->numTileCols * ctx->blockSize);

    ctx->sigma = 0.05;
    ctx->sigma2 = ctx->sigma * ctx->sigma;
    ctx->lambda = 0.065;
    ctx->gamma = ctx->lambda / ctx->sigma2;
    ctx->dt = 5;
    
    // Launch the graph for execution
    RicianDenoising_launch(NULL, ctx);

    return 0;
}
