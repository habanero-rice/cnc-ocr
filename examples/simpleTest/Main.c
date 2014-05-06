
#include "Context.h"

void cncEnvIn(int argc, char **argv, Context *context) {

    //Create and put size    
    int *size;
    cncHandle_t size_handle = cncCreateItem_size(&size);
    *size=10;
    char *tag = CREATE_TAG(0);
    Put(size_handle, tag, context->size);

    //Create and put A
    int *k, i;    
    for (i=0; i<*size; i++){
        ocrGuid_t db_handle = cncCreateItem_Ai(&k, 1);
        *k = i;
        char *tagl = CREATE_TAG(i);
        Put(db_handle, tagl, context->Ai);
    }

    PRINTF("Starting parallel computation\n");

    CNC_PRESCRIBE(Step0, tag, context);

    char *tag2 = CREATE_TAG(2);
    setEnvOutTag(tag2, context);
}

void cncEnvOut(int i, CiItem Ci0, Context *context) {
    PRINTF("Finished parallel computation\n\n");

    char *tag2 = CREATE_TAG(2);
    PRINTF("Result=%d (from tag=%s)\n", *Ci0.item, tag2);
}
