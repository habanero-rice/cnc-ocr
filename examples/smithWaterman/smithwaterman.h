#ifndef _SMITH_WATERMAN_H_
#define _SMITH_WATERMAN_H_

#include <sys/time.h>

#define GAP_PENALTY -1
#define TRANSITION_PENALTY -2
#define TRANSVERSION_PENALTY -4
#define MATCH 2

enum Nucleotide {GAP=0, ADENINE, CYTOSINE, GUANINE, THYMINE};

extern int TW, TH, RW, RH;
extern const signed char *string1, *string2;
extern const char score_matrix[5][5];

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

static inline int max_score(int x, int y) {
    return (x > y) ? x : y;
}

#endif /*_SMITH_WATERMAN_H_*/
