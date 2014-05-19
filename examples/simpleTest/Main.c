
#include "Context.h"

void cncEnvIn(int argc, char **argv, Context *context) {

    //Create and put size    
    int *size;
    cncHandle_t size_handle = cncCreateItem_size(&size);
    *size=10;
    cncPut_size(size_handle, 0, context);

    //Create and put A
    int *k, i;    
    for (i=0; i<*size; i++){
        ocrGuid_t db_handle = cncCreateItem_Ai(&k, 1);
        *k = i;
        cncPut_Ai(db_handle, i, context);
    }

    PRINTF("Starting parallel computation\n");

    cncPrescribe_Step0(0, context);
    cncPrescribe_cncEnvOut(2, context);
}

void cncEnvOut(int i, CiItem Ci0, Context *context) {
    PRINTF("Finished parallel computation\n\n");

    PRINTF("Result=%d (from tag=%d)\n", *Ci0.item, 2);
}
