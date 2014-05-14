
#include "Common.h"
void top_border( int i, int j, AItem A0p, Context *context){
    int (*A0)[TH] = (int(*)[TH])A0p.item;
	int *A11D;
	cncHandle_t A1_handle = cncCreateItem_A(&A11D, TH*TW);
	int (*A1)[TH] = (int(*)[TH])A11D;
    
    int ii, jj;
    signed char char_from_2, char_from_1;	
	int diag_score, left_score, top_score, bigger_of_left_top;
	int start_H = TH-RH;
	int start_W = 0;
	ii=start_H;
	jj=start_W;
	SW_TOP(A1); 
	//A_diag, A_left, A_top, A_out 
	for(jj=start_W+1; jj<TW; jj++){
		SW_TOP(A1); 
	}
	jj=start_W;
	for(ii=start_H+1; ii<TH; ii++) {
		SW_MATRIX(A0, A0, A1, A1);
    		for (jj=start_W+1; jj<TW; jj++) {
			SW_MATRIX(A1, A1, A1, A1);
		}
		jj=start_W;
	}
	ii=start_H;
    
	char *tagA1 = createTag(2, i, j);
	Put(A1_handle, tagA1, context->A);
}


