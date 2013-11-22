
   // ***** AUTO-GENERATED FILE FROM Cholesky.cnc, DO NOT MODIFY!  *****//

#include "cnc_mm.h"
#include "Context.h"

Context* initGraph()
{
	int i;
	Context* CnCGraph = (Context*) cnc_malloc (1 * sizeof(Context));


	CnCGraph->Lkji = (ItemCollectionEntry**) cnc_malloc (TABLE_SIZE * sizeof(ItemCollectionEntry*));
	CnCGraph->numTiles = (ItemCollectionEntry**) cnc_malloc (TABLE_SIZE * sizeof(ItemCollectionEntry*));
	CnCGraph->tileSize = (ItemCollectionEntry**) cnc_malloc (TABLE_SIZE * sizeof(ItemCollectionEntry*));

	for(i=0; i<TABLE_SIZE; i++){
		CnCGraph->Lkji[i] = CnCGraph->numTiles[i] = CnCGraph->tileSize[i] =  NULL;
	}
	return CnCGraph;
}

void deleteGraph(Context* CnCGraph)
{
	cnc_free(CnCGraph->Lkji);
	cnc_free(CnCGraph->numTiles);
	cnc_free(CnCGraph->tileSize);

	cnc_free(CnCGraph);
}

