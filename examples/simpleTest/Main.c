#include "Dispatch.h"
#include <string.h>

ocrGuid_t finishEdt(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]) {
    char* step = (char*)paramv[0];
    char* tag = (char*)paramv[1];
    Context* cncGraph = (Context*)paramv[2];

    PRINTF("In the FinishEDT\n");

    prescribeStep(step,tag,cncGraph);

    return NULL_GUID;
}

ocrGuid_t continuationEdt(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]) {
    Context *context = (Context*)paramv[0];

    PRINTF("Finished parallel computation\n\n");


    char* tag2 = CREATE_TAG(2);
    int* tmpC = depv[1].ptr;
    PRINTF("Result=%d (from tag=%s)\n", *tmpC, tag2);

    deleteGraph(context);
    ocrShutdown();

    return NULL_GUID;
}

ocrGuid_t mainEdt(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]) {
    Context* context = initGraph();

    //Create and put size    
    char* tag = CREATE_TAG(0);
    int* size;
    ocrGuid_t size0_guid;
    ocrDbCreate(&size0_guid, (void **) &size, sizeof(int), 0, NULL_GUID, NO_ALLOC);
    *size=10;
    Put(size0_guid, tag, context->size);

    //Create and put A
    int*k, i;    
    for (i=0; i< *size; i++){
            ocrGuid_t db_guid;
            ocrDbCreate(&db_guid, (void **) &k, sizeof(int), 0, NULL_GUID, NO_ALLOC);
        *k = i;
        char* tagl = CREATE_TAG(i);
        Put(db_guid, tagl, context->Ai);
    }

    //Start graph and wait for it to finish
    ocrGuid_t edt_guid;
    void* f_args [] = {(void*)"Step0",(void*)tag,(void*)context};
    ocrGuid_t done_guid, templ_guid;
    ocrEdtTemplateCreate(&templ_guid, finishEdt, 3, 1);
    ocrEdtCreate(&edt_guid, templ_guid,
                  EDT_PARAM_DEF, /*paramv*/(u64*)f_args,
                  EDT_PARAM_DEF, /*depv=*/NULL, 
                  /*properties=*/EDT_PROP_FINISH,/*affinity*/ NULL_GUID,
                  /*outEvent=*/&done_guid);
    ocrGuid_t contTemplGuid, contGuid;

    // Set up output continuation
    char* tag2 = CREATE_TAG(2);
    ocrGuid_t getOutputGuid = cncGet(tag2, context->Ci);
    ocrEdtTemplateCreate(&contTemplGuid, continuationEdt, 1, 2);
    ocrGuid_t contEdtDeps[] = { done_guid, getOutputGuid };
    ocrEdtCreate(&contGuid, contTemplGuid,
                  EDT_PARAM_DEF, /*paramv*/(u64*)context,
                  EDT_PARAM_DEF, /*depv=*/contEdtDeps, 
                  /*properties=*/EDT_PROP_NONE, /*affinity*/ NULL_GUID,
                  /*outEvent=*/NULL);

    // Start graph
    ocrAddDependence(NULL_GUID, edt_guid, 0, DB_DEFAULT_MODE);

}

