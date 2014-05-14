
   /***** AUTO-GENERATED FILE from file sw.cnc - only generated if file does not exist (on running cncocr_t the first time) - feel free to edit *****/

#include "Context.h"

signed char char_mapping ( char c ) {
	signed char to_be_returned = -1;
	switch(c) {
		case '_': to_be_returned = GAP; break;
		case 'A': to_be_returned = ADENINE; break;
		case 'C': to_be_returned = CYTOSINE; break;
		case 'G': to_be_returned = GUANINE; break;
		case 'T': to_be_returned = THYMINE; break;
	}
	return to_be_returned;
}

size_t clear_whitespaces_do_mapping ( signed char* buffer, long sizet ) {
	size_t non_ws_index = 0, traverse_index = 0;
	while ( traverse_index < sizet ) {
		char curr_char = buffer[traverse_index];
		switch ( curr_char ) {
			case 'A': case 'C': case 'G': case 'T':
			/*this used to be a copy not also does mapping*/
			buffer[non_ws_index++] = char_mapping(curr_char);
			break;
		}
		++traverse_index;
	}
	return non_ws_index;
}

signed char* read_file( FILE* file, size_t* n_chars ) {
	fseek (file, 0L, SEEK_END);
	long file_size = ftell (file);
	fseek (file, 0L, SEEK_SET);

	signed char *file_buffer = (signed char *)malloc((1+file_size)*sizeof(signed char));

	size_t n_read_from_file = fread(file_buffer, sizeof(signed char), file_size, file);
	file_buffer[file_size] = '\n';

	/* shams' sample inputs have newlines in them */
	*n_chars = clear_whitespaces_do_mapping(file_buffer, file_size);
	return file_buffer;
}

const char score_matrix[5][5] =
{
	{GAP_PENALTY,GAP_PENALTY,GAP_PENALTY,GAP_PENALTY,GAP_PENALTY},
	{GAP_PENALTY,MATCH,TRANSVERSION_PENALTY,TRANSITION_PENALTY,TRANSVERSION_PENALTY},
	{GAP_PENALTY,TRANSVERSION_PENALTY, MATCH,TRANSVERSION_PENALTY,TRANSITION_PENALTY},
	{GAP_PENALTY,TRANSITION_PENALTY,TRANSVERSION_PENALTY, MATCH,TRANSVERSION_PENALTY},
	{GAP_PENALTY,TRANSVERSION_PENALTY,TRANSITION_PENALTY,TRANSVERSION_PENALTY, MATCH}
};
int TH, TW, RH, RW;
const signed char *string1, *string2;

void cncEnvIn(int argc, char **argv, Context *context) {

    CNC_REQUIRE(argc == 5, 
                "Usage: %s fileName1 fileName2 tileVertical tileHorizontal\n", argv[0]);

    // Read input and set global variables (all constants)
    char* file_name_1 = argv[1];
	char* file_name_2 = argv[2];
	FILE* file_1 = fopen(file_name_1, "r");
    CNC_REQUIRE(file_1 != NULL, "could not open file %s\n",file_name_1);
	size_t n_char_in_file_1 = 0;
	string1 = read_file(file_1, &n_char_in_file_1);
	PRINTF("Size of input string 1 is %u\n", (unsigned)n_char_in_file_1 );
	FILE* file_2 = fopen(file_name_2, "r");
	CNC_REQUIRE(file_2 != NULL, "could not open file %s\n",file_name_2);
	size_t n_char_in_file_2 = 0;
	string2 = read_file(file_2, &n_char_in_file_2);
	PRINTF("Size of input string 2 is %u\n", (unsigned)n_char_in_file_2 );
	TH = atoi(argv[3]);
    TW = atoi(argv[4]);
	int NH = (n_char_in_file_2+1)/TH, NW = (n_char_in_file_1+1)/TW;
	RH = (n_char_in_file_2+1)%TH;
    RW = (n_char_in_file_1+1)%TW;	
	if(RH==0) {RH+=TH; NH--;}
	if(RW==0) {RW+=TW; NW--;}
    
    // Record the starting time of the computation
    char *tag = CREATE_TAG(0);
    struct timeval *startTime;
    cncHandle_t time_handle = cncCreateItem_startTime(&startTime, 1);
    gettimeofday(startTime, 0);
    Put(time_handle, tag, context->startTime);

    // Start the computation
	char *tagcornerTag3 = CREATE_TAG(0, 0);
	CNC_PRESCRIBE(corner, tagcornerTag3, context);

	int _index1_1;
	for(_index1_1 = 1; _index1_1 < NW+1; _index1_1++){
		char *tagtop_borderTag1 = CREATE_TAG(0, _index1_1);
		CNC_PRESCRIBE(top_border, tagtop_borderTag1, context);
	}

	int _index2_0;
	for(_index2_0 = 1; _index2_0 < NH+1; _index2_0++){
		char *tagleft_borderTag2 = CREATE_TAG(_index2_0, 0);
		CNC_PRESCRIBE(left_border, tagleft_borderTag2, context);
	}

	int _index4_0, _index4_1;
	for(_index4_0 = 1; _index4_0 < NH+1; _index4_0++){
		for(_index4_1 = 1; _index4_1 < NW+1; _index4_1++){
			char *tagfulltileTag4 = CREATE_TAG(_index4_0, _index4_1);
			CNC_PRESCRIBE(fulltile, tagfulltileTag4, context);
		}
	}

    // Set tag for the output step
	char *envOutTag = CREATE_TAG(NH, NW);
	setEnvOutTag(envOutTag, context);
}

void cncEnvOut(int NH, int NW, startTimeItem startTime, AItem A, Context *context) {
	// Report the total running time
    struct timeval endTime;
    gettimeofday(&endTime, 0);
    double secondsRun = endTime.tv_sec - startTime.item->tv_sec;
    secondsRun += (endTime.tv_usec - startTime.item->tv_usec) / 1000000.0;
    PRINTF("The computation took %f seconds\n", secondsRun);
    // Print the result
    int (*result)[TH] = (int(*)[TH])A.item;
    PRINTF("Result is: %d\n", result[TH-1][TW-1]);
}
