#ifndef _CNCOCR_RICIANDENOISING_TYPES_H_
#define _CNCOCR_RICIANDENOISING_TYPES_H_

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "rtwtypes.h"
#include "ricianDenoiseTiled_initialize.h"
#include "ricianDenoiseTiled_terminate.h"
#include "ricianDenoiseTiled_emxAPI.h"
#include "ricianDenoiseTiled.h"

typedef struct RicianDenoisingArguments {
    /* TODO: Add struct members.
     * Use this struct to pass all arguments for
     * graph initialization. This should not contain any
     * pointers (unless you know you'll only be executing
     * in shared memory and thus passing pointers is safe).
     */
} RicianDenoisingArgs;

static inline double user_RicianDenoising_Application_rand(double low, double high) {
  return ( (double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
}

#define TILE_ELEMS (ctx->numTileRows*ctx->numTileCols)

// CONSTANTS

#define RD_DEBUG (0)
#define RD_DEBUG_COMP (RD_DEBUG && 1)
#define RD_DEBUG_LIST (RD_DEBUG && 1)

#define TAG_BLOCK_SIZE (0)
#define TAG_NUM_TILE_ROWS (1)
#define TAG_NUM_TILE_COLS (2)
#define TAG_DT (3)
#define TAG_EPSILON (4)
#define TAG_SIGMA (5)
#define TAG_SIGMA_2 (6)
#define TAG_GAMMA (7)

#define TAG_TOP (0)
#define TAG_RIG (1)
#define TAG_LEF (2)
#define TAG_BOT (3)

void RicianDenoising_tag_tokenize(const char* input, int result[3]);

#endif /*_CNCOCR_RICIANDENOISING_TYPES_H_*/
