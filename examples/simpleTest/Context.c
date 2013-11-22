
   // ***** AUTO-GENERATED FILE FROM simpleTest.cnc, DO NOT MODIFY!  *****//

#include "cnc_mm.h"
#include "Context.h"

Context* initGraph()
{
	int i;
	Context* CnCGraph = (Context*) cnc_malloc (1 * sizeof(Context));


	CnCGraph->Ai = (ItemCollectionEntry**) cnc_malloc (TABLE_SIZE * sizeof(ItemCollectionEntry*));
	CnCGraph->Bi = (ItemCollectionEntry**) cnc_malloc (TABLE_SIZE * sizeof(ItemCollectionEntry*));
	CnCGraph->size = (ItemCollectionEntry**) cnc_malloc (TABLE_SIZE * sizeof(ItemCollectionEntry*));
	CnCGraph->Ci = (ItemCollectionEntry**) cnc_malloc (TABLE_SIZE * sizeof(ItemCollectionEntry*));

	for(i=0; i<TABLE_SIZE; i++){
		CnCGraph->Ai[i] = CnCGraph->Bi[i] = CnCGraph->size[i] = CnCGraph->Ci[i] =  NULL;
	}
	return CnCGraph;
}

void deleteGraph(Context* CnCGraph)
{
	cnc_free(CnCGraph->Ai);
	cnc_free(CnCGraph->Bi);
	cnc_free(CnCGraph->size);
	cnc_free(CnCGraph->Ci);

	cnc_free(CnCGraph);
}

