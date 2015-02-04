#include "Cholesky.h"

int main(int argc, char **argv) {

    CNC_REQUIRE(OCR_MAIN_ARGC==4,
            "Usage: ./Cholesky matrixSize tileSize fileName (found %d args)\n", OCR_MAIN_ARGC);

    // Create a new graph context
    CholeskyCtx *context = Cholesky_create();

    // Parse matrix dim info
    int matrixCols = atoi(OCR_MAIN_ARGV(1));
    int tileSize = atoi(OCR_MAIN_ARGV(2));
    int numTiles = matrixCols / tileSize;
    CNC_REQUIRE(matrixCols % tileSize == 0,
            "Incompatible tile size %d for the matrix of size %d\n", tileSize, matrixCols);

    // Set graph parameters
    context->numTiles = numTiles;
    context->tileSize = tileSize;

    // Set up arguments for new graph instantiation
    const char *inFile = OCR_MAIN_ARGV(3);
    CholeskyArgs args = { inFile };

    // Launch the graph for execution
    Cholesky_launch(&args, context);

    return 0;
}
