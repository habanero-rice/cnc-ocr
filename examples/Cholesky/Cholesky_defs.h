#ifndef _CNCOCR_CHOLESKY_TYPES_H_
#define _CNCOCR_CHOLESKY_TYPES_H_

#if CNCOCR_x86
#include <sys/time.h>
#endif

typedef struct CholeskyArguments {
    // Path to input matrix file
    const char *inFile;
} CholeskyArgs;

#endif /*_CNCOCR_CHOLESKY_TYPES_H_*/
