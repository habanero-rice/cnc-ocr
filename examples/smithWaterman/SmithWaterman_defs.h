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
    s32 tw, th, ntw, nth;
} SmithWatermanArgs;

static inline int wave_dist(int i, int j, int N, int P) {
  const int x = i + j + 1;
  const int diag_length = (x < N) ? x : (x - ((x - N) * 2));
  const int c = diag_length / P;
  const int r = diag_length % P;
  int p = (diag_length <= P)
            ? (
                (x < N)
                  ? (i)
                  : (N - (j + 1))
              )
            : (
                (x < N)
                  ? (
                      (i > ((r * c) + r))
                        ? (((i - ((r * c) + r)) / c) + r)
                        : (i / (c + 1))
                    )
                  : (
                      ((N - (j + 1)) > ((r * c) + r))
                        ? ((((N - (j + 1)) - ((r * c) + r)) / c) + r)
                        : ((N - (j + 1)) / (c + 1))
                    )
              );
  assert(0 <= p);
  assert(p < P);
  return p;
}

#endif /*_CNCOCR_SMITHWATERMAN_TYPES_H_*/
