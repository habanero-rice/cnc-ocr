#include "Cholesky.h"
/* Chunked distribution */
#define XTUNING_DISTRIBUTE_AMONG_CHILDREN(nNum, nName, aArray) {			\
	int i, j, p;														\
	place_t * pl = hc_get_current_place();								\
	int chunk_size = nNum / pl->nChildren;								\
	int chunk_rem = nNum % pl->nChildren;								\
	i = 0; 																\
	p = 0;																\
	while (i < nNum) {													\
         fprintf(stderr, "%d is pl\n", pl->nChildren);\
		place_t * ch = ((place_t *)pl->children[p])->tuning_place;		\
         fprintf(stderr, "%p is place\n", ch);\
		int ub = (p < chunk_rem) ? i+chunk_size+1 : i+chunk_size;		\
		for (j = i ; j < ub; j++) {										\
			void * a = (void*)aArray[j];								\
			async (ch) IN(a) { nName(a); }								\
		}																\
		i = ub;															\
		p++;															\
	}																	\
}

/*
 */
#pragma hc continuable
void kComputeStep(cncTag_t k, CholeskyCtx *ctx) {
    cncTag_t *kp = malloc(sizeof(k));
    *kp = k;
    TUNING_RELEASE_STEP(cncPrescribeT_s1ComputeStep, kp);
    int j;
    int numTU = ctx->numTiles - (k + 1);
    cncTag_t **childTags = malloc(sizeof(cncTag_t*) * numTU);
    for (j=0; j<numTU; j++) {
        childTags[j] = malloc(sizeof(cncTag_t)*2);
        childTags[j][0] = k;
        childTags[j][1] = j;
    }
    fprintf(stderr, "k=%d, n=%d\n", k, numTU);
    finish {
    XTUNING_DISTRIBUTE_AMONG_CHILDREN(numTU, cncPrescribeT_kjComputeStep, childTags);
    }
}
