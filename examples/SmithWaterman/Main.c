#include "SmithWaterman.h"
#include <stdio.h>
#include <string.h>

static char ALIGNMENT_SCORES[5][5] = {
    {GAP_PENALTY,GAP_PENALTY,GAP_PENALTY,GAP_PENALTY,GAP_PENALTY},
    {GAP_PENALTY,MATCH,TRANSVERSION_PENALTY,TRANSITION_PENALTY,TRANSVERSION_PENALTY},
    {GAP_PENALTY,TRANSVERSION_PENALTY, MATCH,TRANSVERSION_PENALTY,TRANSITION_PENALTY},
    {GAP_PENALTY,TRANSITION_PENALTY,TRANSVERSION_PENALTY, MATCH,TRANSVERSION_PENALTY},
    {GAP_PENALTY,TRANSVERSION_PENALTY,TRANSITION_PENALTY,TRANSVERSION_PENALTY, MATCH}
};

static inline signed char char_mapping(char c) {
    switch(c) {
        case '_': return GAP;
        case 'A': return ADENINE;
        case 'C': return CYTOSINE;
        case 'G': return GUANINE;
        case 'T': return THYMINE;
    }
    return -1;
}

static FILE *open_file(const char *fileName) {
    FILE *f = fopen(fileName, "r");
    CNC_REQUIRE(f, "Could not open file: %s\n", fileName);
    return f;
}

static size_t file_length(FILE *file) {
    fseek(file, 0L, SEEK_END);
    size_t len = (size_t)ftell(file);
    fseek(file, 0L, SEEK_SET);
    return len;
}

static size_t read_sequence(FILE *file, int fnum, signed char *dest, size_t fsize) {
    fread(dest, sizeof(char), fsize, file);
    size_t seqlen = 0, traverse_index = 0;
    while ( traverse_index < fsize ) {
        char curr_char = dest[traverse_index];
        switch ( curr_char ) {
        case 'A': case 'C': case 'G': case 'T':
            dest[seqlen++] = char_mapping(curr_char);
            break;
        }
        ++traverse_index;
    }
    dest[seqlen] = '\0';
    PRINTF("Size of input sequence %d has length %lu\n", fnum, seqlen);
    return seqlen;
}

ocrGuid_t mainEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    CNC_REQUIRE(OCR_MAIN_ARGC == 5, "Usage: %s fileName1 fileName2 tileWidth tileHeight\n", OCR_MAIN_ARGV(0));

    // Open sequence input files
    FILE *file1 = open_file(OCR_MAIN_ARGV(1));
    FILE *file2 = open_file(OCR_MAIN_ARGV(2));
    size_t filesize1 = file_length(file1);
    size_t filesize2 = file_length(file2);

    // Allocate tile data item and read sequence data
    SeqData *data;
    size_t dataSize = sizeof(SeqData) + filesize1 + filesize2 + 2;
    cncHandle_t dataHandle = cncCreateItemSized_data(&data, dataSize);
    data->seq2offset = filesize1 + 1;
    size_t length1 = read_sequence(file1, 1, SEQ1(data), filesize1);
    size_t length2 = read_sequence(file2, 2, SEQ2(data), filesize2);

    // Tile width and height
    int tw = atoi(OCR_MAIN_ARGV(3));
    int th = atoi(OCR_MAIN_ARGV(4));
    PRINTF("Tile width:  %d\n", tw);
    PRINTF("Tile height: %d\n", th);
    CNC_REQUIRE(tw <= length1 && th <= length2, "Tile size too large for given input.\n");

    // Number of tiles wide and high
    s32 ntw = length1 / tw;
    s32 nth = length2 / th;
    PRINTF("Imported %d x %d tiles.\n", ntw, nth);

    // Initialize tile dimension data and put
    data->tw = tw;
    data->th = th;
    data->ntw = ntw;
    data->nth = nth;
    memcpy(data->score_matrix, ALIGNMENT_SCORES, sizeof(ALIGNMENT_SCORES));

    // Create a new graph context
    SmithWatermanCtx *context = SmithWaterman_create();
    
    // Set up arguments for new graph instantiation
    SmithWatermanArgs args = { tw, th, ntw, nth, dataHandle };

    // Exit when the graph execution completes
    CNC_SHUTDOWN_ON_FINISH(context);

    // Launch the graph for execution
    SmithWaterman_launch(&args, context);

    return NULL_GUID;
}
