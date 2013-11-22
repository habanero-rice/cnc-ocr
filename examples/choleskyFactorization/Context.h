
   // ***** AUTO-GENERATED FILE FROM Cholesky.cnc, DO NOT MODIFY!  *****//

#ifndef _CONTEXT
#define _CONTEXT

#include "DataDriven.h"

struct Context
{
	ItemCollectionEntry ** Lkji;
	ItemCollectionEntry ** numTiles;
	ItemCollectionEntry ** tileSize;
};
typedef struct Context Context;

struct Context* initGraph();
void deleteGraph(Context* CnCGraph);

#endif /*_CONTEXT*/

