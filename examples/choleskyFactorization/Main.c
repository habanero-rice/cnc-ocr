
   /***** AUTO-GENERATED FILE from file Cholesky.cnc - only generated if file does not exist (on running cncc_t the first time) - feel free to edit *****/

#include "Dispatch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <ocr-lib.h>

#define FLAGS 0xdead

ocrGuid_t finishEdt ( u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]) {
    char* step = (char*)paramv[0];
    char* tag = (char*)paramv[1];
    Context* cncGraph = (Context*)paramv[2];

    printf("In the FinishEDT\n");

    prescribeStep(step,tag,cncGraph);

    return NULL_GUID;
}

int main(int argc, const char** argv)
{

	if(!(argc ==  4))
	{
		printf("Usage: ./Cholesky matrixSize tileSize fileName (found %d args)\n", argc);
		return 1;
	}
	ocrConfig_t ocrConfig;
	ocrParseArgs(argc, argv, &ocrConfig);
	ocrInit(&ocrConfig);

	int i, j;
	int i_b, j_b;
	int A_i, A_j, T_i, T_j, ii;
	FILE*f;
	FILE * ff = fopen("Cholesky.out", "w");
        char* tag;   
 
	double** local_tile;
	double ** A;
	int *n, *t, *nt ;
	ocrGuid_t n_guid, t_guid, nt_guid;

	n = malloc(1 * sizeof(int));
	ocrDbCreate(&t_guid, (void **) &t, sizeof(int), /*flags=*/FLAGS,/*location=*/NULL_GUID, NO_ALLOC);
	ocrDbCreate(&nt_guid, (void **) &nt, sizeof(int), /*flags=*/FLAGS,/*location=*/NULL_GUID, NO_ALLOC);
	*n = atoi(argv[1]);
	*t = atoi(argv[2]);
	if ((*n) % (*t) != 0){
		printf("Incorrect tile size %d for the matrix of size %d \n", *t, *n);
		return 1;
	}
	
	*nt = (*n)/(*t);
	f = fopen(argv[3], "r");
	if( f == NULL )
	{
		printf("Cannot find file: %s\n", argv[3]);
		//TODO: cleanup OCR
		return 1;
	}
	A = (double**) malloc ((*n) * sizeof(double*)) ;
	for(i=0; i<(*n); i++)
		A[i] = (double*) malloc((*n) * sizeof(double));
	for(i=0; i<(*n); i++)
	{
		for(j=0; j<(*n)-1; j++)
			fscanf(f, "%lf ", &A[i][j]);
		fscanf(f, "%lf\n", &A[i][j]);
	}

	Context* CnCGraph = initGraph();
	tag = createTag(1, 0);
	Put(nt_guid, tag, CnCGraph->numTiles);
	Put(t_guid, tag, CnCGraph->tileSize);
    
	for(i=0; i < (*nt); i++){
		for( j = 0 ; j <= i ; ++j ) {
        		ocrGuid_t db_guid;
			double **temp;
			ocrDbCreate(&db_guid, (void **) &temp, (*t) * sizeof(double*), FLAGS, NULL_GUID, NO_ALLOC);
			for(ii = 0; ii < (*t); ii++)
				temp[ii] = (double*) malloc ( (*t) * sizeof(double) ); //HACK!!!
			for( A_i = i * (*t), T_i = 0 ; T_i < (*t) ; ++A_i, ++T_i ) {
				for( A_j = j * (*t), T_j = 0 ; T_j < (*t) ; ++A_j, ++T_j ) {
					//printf("%d %d %d %d\n", T_i, T_j, A_i, A_j);
					temp[ T_i ][ T_j ] = A[ A_i ][ A_j ];
				}
			}
			
			char * tempTag = createTag(3, i, j, 0);
			Put(db_guid, tempTag, CnCGraph->Lkji);
		}
	}
	
	struct timeval a;
	struct timeval b;
	gettimeofday(&a, 0);
	
	ocrGuid_t edt_guid;
	void* f_args [] = {(void*)"kComputeStep",(void*)tag,(void*)CnCGraph};
	ocrGuid_t done_guid, templ_guid;
	ocrEdtTemplateCreate(&templ_guid, finishEdt, 3, 0);
	ocrEdtCreate(&edt_guid, templ_guid, /*paramc=*/3, /*paramv*/(u64*)f_args,
                  /*depc=*/0, /*depv=*/NULL, 
                  /*properties=*/EDT_PROP_FINISH,/*affinity*/ 0,
                  /*outEvent=*/&done_guid);
	ocrWait(done_guid);

	gettimeofday(&b, 0);
        printf("The computation took Q%fQ seconds\r\n",((b.tv_sec - a.tv_sec)*1000000+(b.tv_usec - a.tv_usec))*1.0/1000000);

	for ( i = 0; i < (*nt); i++) {
		for( i_b = 0; i_b < (*t); i_b++) {
			int k = 1;
			for ( j = 0; j <= i; j++) {
				char * tempTag = createTag(3, i, j, k);
				//local_tile=NULL;
				cncGet((void**)&local_tile, tempTag, CnCGraph->Lkji);
				//assert(local_tile != NULL);
				if(i != j) {
					for(j_b = 0; j_b < (*t); j_b++) {
						fprintf(ff, "%lf ", local_tile[i_b][j_b]);
					}
				} 
				else {
					for(j_b = 0; j_b <= i_b; j_b++) {
						fprintf(ff, "%lf ", local_tile[i_b][j_b]);
					}
				}
			k++;
			}
		}
	}
	
	ocrShutdown();
	ocrFinalize();
	
	deleteGraph(CnCGraph);

	free(tag);
	for(i=0; i<(*n); i++)
                free(A[i]);
	free(A);
	//TODO: Delete datablocks for n, nt, t, etc.
	return 0;
}

