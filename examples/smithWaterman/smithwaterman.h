#ifndef _SMITH_WATERMAN_H_
#define _SMITH_WATERMAN_H_

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
    int tw, th, ntw, nth;
    int seq2offset;
    signed char score_matrix[5][5];
    signed char strings[]; 
} SeqData;

#endif /*_SMITH_WATERMAN_H_*/
