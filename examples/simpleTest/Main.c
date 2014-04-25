
#include "Dispatch.h"

void cncEnvIn(int argc, char **argv, Context *context) {
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

    PRINTF("In the FinishEDT\n");

    prescribeStep("Step0", tag, context);

    char* tag2 = CREATE_TAG(2);
    setEnvOutTag(tag2, context);
}

void cncEnvOut(int i, CiItem Ci0, Context* context) {
    PRINTF("Finished parallel computation\n\n");

    char* tag2 = CREATE_TAG(2);
    PRINTF("Result=%d (from tag=%s)\n", *Ci0.item, tag2);
}
