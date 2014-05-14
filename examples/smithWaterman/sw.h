#ifndef _SW_H
#define _SW_H

#define GAP_PENALTY -1
#define TRANSITION_PENALTY -2
#define TRANSVERSION_PENALTY -4
#define MATCH 2

enum Nucleotide {GAP=0, ADENINE, CYTOSINE, GUANINE, THYMINE};

extern int TW, TH, RW, RH;
extern const signed char *string1, *string2;
extern const char score_matrix[5][5];

/*struct sw { 
	int tw, th, rw, rh;
    int size1;
    char score_matrix[5][5];
	char strings[]; 
};*/

#define SW_BORDER(A_out){\
	 A_out[ii][jj] = GAP_PENALTY * ((i-1)*TH+RH + ii + (j-1)*TW+RW + jj);\
}

#define SW_CORNER(A_out){\
	 A_out[ii][jj] = 0;\
}

#define SW_TOP(A_out){\
	 A_out[ii][jj] = GAP_PENALTY * ((j-1)*TW+RW + jj);\
}

#define SW_LEFT(A_out){\
	 A_out[ii][jj] = GAP_PENALTY * ((i-1)*TH+RH + ii);\
}

#define SW_MATRIX(A_diag, A_left, A_top, A_out) {\
			char_from_2 = string2[(i-1)*TH+RH + (ii-1)]; \
			char_from_1 = string1[(j-1)*TW+RW + (jj-1)]; \
						diag_score = A_diag[(ii-1+TH)%TH][(jj-1+TW)%TW] + score_matrix[char_from_2][char_from_1];\
						left_score = A_left[ii][(jj-1+TW)%TW] + score_matrix[char_from_1][GAP];\
						top_score = A_top[(ii-1+TH)%TH][jj] + score_matrix[GAP][char_from_2];\
						bigger_of_left_top = (left_score > top_score) ? left_score : top_score;\
						A_out[ii][jj] = (bigger_of_left_top > diag_score) ? bigger_of_left_top : diag_score;\
}

#endif /*_SW_H*/
