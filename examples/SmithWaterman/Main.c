#include "SmithWaterman.h"
#include <string.h>

void copy_path(char *dest, const char *src, u32 dest_len) {
    strncpy(dest, src, dest_len);
    CNC_REQUIRE(dest[dest_len-1] == '\0', "Input path length too long (max %u)\n", dest_len);
}

ocrGuid_t mainEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    CNC_REQUIRE(OCR_MAIN_ARGC == 5, "Usage: %s fileName1 fileName2 tileWidth tileHeight\n", OCR_MAIN_ARGV(0));

    // Tile width and height
    int tw = atoi(OCR_MAIN_ARGV(3));
    int th = atoi(OCR_MAIN_ARGV(4));
    PRINTF("Tile width:  %d\n", tw);
    PRINTF("Tile height: %d\n", th);

    // Create a new graph context
    SmithWatermanCtx *context = SmithWaterman_create();

    // Set up arguments for new graph instantiation
    SmithWatermanArgs args;
    args.tw = tw;
    args.th = th;
    copy_path(args.inpath1, OCR_MAIN_ARGV(1), sizeof(args.inpath1));
    copy_path(args.inpath2, OCR_MAIN_ARGV(2), sizeof(args.inpath2));

    // Exit when the graph execution completes
    CNC_SHUTDOWN_ON_FINISH(context);

    // Launch the graph for execution
    SmithWaterman_launch(&args, context);

    return NULL_GUID;
}
