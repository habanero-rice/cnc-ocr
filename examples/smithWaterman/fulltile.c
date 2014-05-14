
#include "Common.h"
void fulltile( int i, int j, AItem A0p, AItem A1p, AItem A2p, Context *context){
    int (*A0)[TH] = (int(*)[TH])A0p.item;
    int (*A1)[TH] = (int(*)[TH])A1p.item;
    int (*A2)[TH] = (int(*)[TH])A2p.item;
	int *A31D;
	cncHandle_t A3_handle = cncCreateItem_A(&A31D, TH*TW);
	int (*A3)[TH] = (int(*)[TH])A31D;

    int ii, jj;
    signed char char_from_2, char_from_1;	
	int diag_score, left_score, top_score, bigger_of_left_top;
	int start_H = 0;
	int start_W = 0;
	ii=start_H;
	jj=start_W;
	SW_MATRIX(A2, A1, A0, A3);
	//A_diag, A_left, A_top, A_out 
	//A2=diag; A1=left; A0=top, A3=out
	for(jj=start_W+1; jj<TW; jj++){
		SW_MATRIX(A0, A3, A0, A3);
	}
	jj=start_W;
	for(ii=start_H+1; ii<TH; ii++) {
		SW_MATRIX(A1, A1, A3, A3);
    		for (jj=start_W+1; jj<TW; jj++) {
			SW_MATRIX(A3, A3, A3, A3);
		}
		jj=start_W;
	}
	ii=start_H;
    
	char *tagA3 = createTag(2, i, j);
	Put(A3_handle, tagA3, context->A);
}


