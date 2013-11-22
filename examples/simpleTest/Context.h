
   // ***** AUTO-GENERATED FILE FROM simpleTest.cnc, DO NOT MODIFY!  *****//

#ifndef _CONTEXT
#define _CONTEXT

#include "DataDriven.h"

struct Context
{
	ItemCollectionEntry ** Ai;
	ItemCollectionEntry ** Bi;
	ItemCollectionEntry ** size;
	ItemCollectionEntry ** Ci;
};
typedef struct Context Context;

struct Context* initGraph();
void deleteGraph(Context* CnCGraph);

#endif /*_CONTEXT*/

