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


void SmithWaterman_init(SmithWatermanArgs *args, SmithWatermanCtx *ctx) {

    // Unpack arguments
    s32 tw = args->tw;
    s32 th = args->th;
    s32 nth, ntw;

    // Open sequence input files
    FILE *file1 = open_file(args->inpath1);
    FILE *file2 = open_file(args->inpath2);
    size_t filesize1 = file_length(file1);
    size_t filesize2 = file_length(file2);

    // Allocate tile data item and read sequence data
    size_t dataSize = sizeof(SeqData) + filesize1 + filesize2 + 2;
    SeqData *data = cncCreateItemSized_data(dataSize);
    data->seq2offset = filesize1 + 1;
    size_t length1 = read_sequence(file1, 1, SEQ1(data), filesize1);
    size_t length2 = read_sequence(file2, 2, SEQ2(data), filesize2);
    CNC_REQUIRE(tw <= length1 && th <= length2, "Tile size too large for given input.\n");

    // Initialize tile dimensions and scores
    data->tw = tw;
    data->th = th;
    data->ntw = ntw = length1 / tw;
    data->nth = nth = length2 / th;
    memcpy(data->score_matrix, ALIGNMENT_SCORES, sizeof(ALIGNMENT_SCORES));

    // Done initializing data
    cncPut_data(data, ctx);
    fclose(file1);
    fclose(file2);
    PRINTF("Imported %d x %d tiles.\n", ntw, nth);

    // Record starting time
    struct timeval *startTime = cncCreateItem_startTime();
    gettimeofday(startTime, 0);
    cncPut_startTime(startTime, ctx);

    // Seed edges
    cncPrescribe_initAboveStep(tw, ntw, ctx);
    cncPrescribe_initLeftStep(th, nth, ctx);

    { // Prescribe "swStep" steps
        s64 _i, _j;
        for (_i = 0; _i < nth; _i++) {
            for (_j = 0; _j < ntw; _j++) {
                cncPrescribe_swStep(_i, _j, ctx);
            }
        }
    }

    // Set finalizer function's tag
    SmithWaterman_await(ntw, nth, tw, ctx);
}


void SmithWaterman_finalize(cncTag_t ntw, cncTag_t nth, cncTag_t tw, struct timeval *startTime, int *above, SmithWatermanCtx *ctx) {
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double secondsRun = endTime.tv_sec - startTime->tv_sec;
    secondsRun += (endTime.tv_usec - startTime->tv_usec) / 1000000.0;
    PRINTF("The computation took %f seconds\n", secondsRun);
    // Print the result
    PRINTF("score: %d\n", above[tw]);
}

