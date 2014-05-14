
#include "Common.h"
void corner( int i, int j, Context *context){
	int *A01D;
	cncHandle_t A0_handle = cncCreateItem_A(&A01D, TH*TW);
    int (*A0)[TH] = (int(*)[TH])A01D;
    
    int ii, jj;
	signed char char_from_2, char_from_1;	
	int diag_score, left_score, top_score, bigger_of_left_top;
	int start_H = TH-RH;
	int start_W = TW-RW;
	ii=start_H;
	jj=start_W;
	SW_CORNER(A0);
	//A_diag, A_left, A_top, A_out 
	for(jj=start_W+1; jj<TW; jj++){
		SW_TOP(A0);
	}
	jj=start_W;
	for(ii=start_H+1; ii<TH; ii++) {
		SW_LEFT(A0);
    		for (jj=start_W+1; jj<TW; jj++) {
			SW_MATRIX(A0, A0, A0, A0);
		}
		jj=start_W;
	}
	ii=start_H;
    
	char *tagA0 = createTag(2, i, j);
	Put(A0_handle, tagA0, context->A);
}


