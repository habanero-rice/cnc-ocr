
   // ***** AUTO-GENERATED FILE FROM simpleTest.cnc, DO NOT MODIFY!  *****//

#include "Dispatch.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

void prescribeStep(char* stepName, char* stepTag, Context* context){
	if(!strncmp(stepName, "Step2\0", 5)){
		int k = getTag(stepTag, 0);
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, Step2_gets, 2, 0 + 1);
		void** args = (void**)cnc_malloc(2*sizeof(void*));
		args[0] = (void*) stepTag;
		args[1] = context;
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/2, /*paramv=*/(u64*)args,
			/*depc=*/0 + 1, /*depv=*/NULL,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL_GUID);
		Step2_dependencies(stepTag, edt_guid, context);
		return;
	}
	if(!strncmp(stepName, "Step1\0", 5)){
		int k = getTag(stepTag, 0);
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, Step1_gets, 2, 0 + 1);
		void** args = (void**)cnc_malloc(2*sizeof(void*));
		args[0] = (void*) stepTag;
		args[1] = context;
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/2, /*paramv=*/(u64*)args,
			/*depc=*/0 + 1, /*depv=*/NULL,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL_GUID);
		Step1_dependencies(stepTag, edt_guid, context);
		return;
	}
	if(!strncmp(stepName, "Step0\0", 5)){
		int k = getTag(stepTag, 0);
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, Step0_gets, 2, 0 + 1);
		void** args = (void**)cnc_malloc(2*sizeof(void*));
		args[0] = (void*) stepTag;
		args[1] = context;
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/2, /*paramv=*/(u64*)args,
			/*depc=*/0 + 1, /*depv=*/NULL,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL_GUID);
		Step0_dependencies(stepTag, edt_guid, context);
		return;
	}
	printf("Step %s not defined\n", stepName);
	assert(0);
}

