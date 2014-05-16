
   /***** AUTO-GENERATED FILE from file SmithWaterman.cnc - only generated if file does not exist (on running cncocr_t the first time) - feel free to edit *****/

#include "Context.h"
#include <string.h>

static char ALIGNMENT_SCORES[5][5] = {
    {GAP_PENALTY,GAP_PENALTY,GAP_PENALTY,GAP_PENALTY,GAP_PENALTY},
    {GAP_PENALTY,MATCH,TRANSVERSION_PENALTY,TRANSITION_PENALTY,TRANSVERSION_PENALTY},
    {GAP_PENALTY,TRANSVERSION_PENALTY, MATCH,TRANSVERSION_PENALTY,TRANSITION_PENALTY},
    {GAP_PENALTY,TRANSITION_PENALTY,TRANSVERSION_PENALTY, MATCH,TRANSVERSION_PENALTY},
    {GAP_PENALTY,TRANSVERSION_PENALTY,TRANSITION_PENALTY,TRANSVERSION_PENALTY, MATCH}
};

static inline FILE *open_file(const char *fileName) {
    FILE *f = fopen(fileName, "r");
    CNC_REQUIRE(f, "Could not open file: %s\n", fileName);
}

static inline size_t file_length(FILE *file) {
    fseek(file, 0L, SEEK_END);
    size_t len = (size_t)ftell(file);
    fseek(file, 0L, SEEK_SET);
    return len;
}

static inline size_t read_sequence(FILE *file, int fnum, signed char *dest, size_t fsize) {
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
    PRINTF("Size of input sequence %d has length %zu\n", fnum, seqlen);
    return seqlen;
}

void cncEnvIn(int argc, char **argv, Context *context) {
    CNC_REQUIRE(argc == 5, "Usage: %s fileName1 fileName2 tileWidth tileHeight\n", argv[0]);

    // Open sequence input files
    FILE *file1 = open_file(argv[1]);
    FILE *file2 = open_file(argv[2]);
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
    int tw = atoi(argv[3]);
    int th = atoi(argv[4]);
    PRINTF("Tile width:  %d\n", tw);
    PRINTF("Tile height: %d\n", th);
    CNC_REQUIRE(tw <= length1 && th <= length2, "Tile size too large for given input.\n");

    // Number of tiles wide and high
    int ntw = length1 / tw;
    int nth = length2 / th;
    PRINTF("Imported %d x %d tiles.\n", ntw, nth);

    // Initialize tile dimension data and put
    data->tw = tw;
    data->th = th;
    data->ntw = ntw;
    data->nth = nth;
    memcpy(data->score_matrix, ALIGNMENT_SCORES, sizeof(ALIGNMENT_SCORES));
    Put(dataHandle, CREATE_TAG(0), context->data);

    // Record starting time
    struct timeval *startTime;
    cncHandle_t startTime_handle = cncCreateItem_startTime(&startTime, 1);
    gettimeofday(startTime, 0);
    Put(startTime_handle, CREATE_TAG(0), context->startTime);

    // Seed edges
    CNC_PRESCRIBE(initAboveStep, CREATE_TAG(tw, ntw), context);
    CNC_PRESCRIBE(initLeftStep,  CREATE_TAG(th, nth), context);

    int i, j;
    for(i = 0; i < nth; i++){
        for(j = 0; j < ntw; j++){
            CNC_PRESCRIBE(swStep, CREATE_TAG(i, j), context);
        }
    }

    setEnvOutTag(CREATE_TAG(ntw, nth, tw), context);
}

void cncEnvOut(int ntw, int nth, int tw, startTimeItem startTime, aboveItem above, Context *context) {
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double secondsRun = endTime.tv_sec - startTime.item->tv_sec;
    secondsRun += (endTime.tv_usec - startTime.item->tv_usec) / 1000000.0;
    PRINTF("The computation took %f seconds\n", secondsRun);
    // Print the result
    PRINTF("score: %d\n", above.item[tw]);
}
