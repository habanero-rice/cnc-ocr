#ifndef _CNCOCR_SMITHWATERMAN_TYPES_H_
#define _CNCOCR_SMITHWATERMAN_TYPES_H_

#include <sys/time.h>

#define GAP_PENALTY -1
#define TRANSITION_PENALTY -2
#define TRANSVERSION_PENALTY -4
#define MATCH 2

enum Nucleotide {GAP=0, ADENINE, CYTOSINE, GUANINE, THYMINE};

#define SEQ1(seqDataPtr) ((seqDataPtr)->strings)
#define SEQ2(seqDataPtr) ((seqDataPtr)->strings+(seqDataPtr)->seq2offset)

#define TSEQ1(seqDataPtr) ((char(*)[(seqDataPtr)->tw])SEQ1(seqDataPtr))
#define TSEQ2(seqDataPtr) ((char(*)[(seqDataPtr)->th])SEQ2(seqDataPtr))

typedef struct {
    s32 tw, th, ntw, nth;
    s32 seq2offset;
    signed char score_matrix[5][5];
    signed char strings[];
} SeqData;

typedef struct SmithWatermanArguments {
    s32 tw, th;
    char inpath1[256];
    char inpath2[256];
} SmithWatermanArgs;

#endif /*_CNCOCR_SMITHWATERMAN_TYPES_H_*/
