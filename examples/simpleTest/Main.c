#include "Dispatch.h"
#include <string.h>
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
	ocrConfig_t ocrConfig;
	ocrParseArgs(argc, argv, &ocrConfig);
	ocrInit(&ocrConfig);
	Context* context = initGraph();

	//Create and put size	
	char* tag = createTag(1, 0);
	int* size;
	ocrGuid_t size0_guid;
	ocrDbCreate(&size0_guid, (void **) &size, sizeof(int), FLAGS, NULL_GUID, NO_ALLOC);
	*size=10;
	Put(size0_guid, tag, context->size);

	//Create and put A
	int*k, i;	
	for (i=0; i< *size; i++){
        	ocrGuid_t db_guid;
        	ocrDbCreate(&db_guid, (void **) &k, sizeof(int), FLAGS, NULL_GUID, NO_ALLOC);
		*k = i;
		char* tagl = createTag(1, i);
		Put(db_guid, tagl, context->Ai);
    	}

	//Start graph and wait for it to finish
	ocrGuid_t edt_guid;
	void* f_args [] = {(void*)"Step0",(void*)tag,(void*)context};
	ocrGuid_t done_guid, templ_guid;
	ocrEdtTemplateCreate(&templ_guid, finishEdt, 3, 0);
	ocrEdtCreate(&edt_guid, templ_guid, /*paramc=*/3, /*paramv*/(u64*)f_args,
                  /*depc=*/0, /*depv=*/NULL, 
                  /*properties=*/EDT_PROP_FINISH,/*affinity*/ 0,
                  /*outEvent=*/&done_guid);
	ocrWait(done_guid);
	printf("Finished parallel computation\n\n");


	char* tag2 = createTag(1, 2);
	int* tmpC = 0x1;
	cncGet((void**) & tmpC, tag2, context->Ci);
	printf("Rez: %p %s\n", tmpC, tag2);

	//Read results
	/*int _index2_0;
	int** Ci2;
	Ci2 = (int**) malloc ( sizeof(int*) * (*size) );

	for(_index2_0 = 0; _index2_0 < *size; _index2_0++){
		char* tagCi2 = createTag(1, _index2_0);
		int* tmpC = 0x1;
            	cncGet((void**) & tmpC, tagCi2, context->Ci);
		printf("%p %s\n", tmpC, tagCi2);
            	//cncGet((void**) & (Ci2[_index2_0]), tagCi2, context->Ci);
		//printf("%p\n", Ci2[_index2_0]);
		//printf("%d\n", Ci2[_index2_0][0]);
	}
	free(Ci2);
	*/
	ocrShutdown();
	ocrFinalize();
	deleteGraph(context);
}

