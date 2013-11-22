
   // ***** AUTO-GENERATED FILE FROM Cholesky.cnc, DO NOT MODIFY!  *****//

#include "Dispatch.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

void prescribeStep(char* stepName, char* stepTag, Context* context){
	if(!strncmp(stepName, "kComputeStep\0", 12)){
		int k = getTag(stepTag, 0);
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, kComputeStep_gets, 2, 0 + 1);
		void** args = (void**)cnc_malloc(2*sizeof(void*));
		args[0] = (void*) stepTag;
		args[1] = context;
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/2, /*paramv=*/(u64*)args,
			/*depc=*/0 + 1, /*depv=*/NULL,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL_GUID);
		kComputeStep_dependencies(stepTag, edt_guid, context);
		return;
	}
	if(!strncmp(stepName, "s2ComputeStep\0", 13)){
		int k = getTag(stepTag, 0);
		int j = getTag(stepTag, 1);
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, s2ComputeStep_gets, 2, 0 + 1*1*1 + 1*1*1 + 1);
		void** args = (void**)cnc_malloc(2*sizeof(void*));
		args[0] = (void*) stepTag;
		args[1] = context;
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/2, /*paramv=*/(u64*)args,
			/*depc=*/0 + 1*1*1 + 1*1*1 + 1, /*depv=*/NULL,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL_GUID);
		s2ComputeStep_dependencies(stepTag, edt_guid, context);
		return;
	}
	if(!strncmp(stepName, "kjComputeStep\0", 13)){
		int k = getTag(stepTag, 0);
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, kjComputeStep_gets, 2, 0 + 1);
		void** args = (void**)cnc_malloc(2*sizeof(void*));
		args[0] = (void*) stepTag;
		args[1] = context;
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/2, /*paramv=*/(u64*)args,
			/*depc=*/0 + 1, /*depv=*/NULL,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL_GUID);
		kjComputeStep_dependencies(stepTag, edt_guid, context);
		return;
	}
	if(!strncmp(stepName, "s3ComputeStep\0", 13)){
		int k = getTag(stepTag, 0);
		int j = getTag(stepTag, 1);
		int i = getTag(stepTag, 2);
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, s3ComputeStep_gets, 2, 0 + 1*1*1 + 1*1*1 + 1*1*1 + 1);
		void** args = (void**)cnc_malloc(2*sizeof(void*));
		args[0] = (void*) stepTag;
		args[1] = context;
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/2, /*paramv=*/(u64*)args,
			/*depc=*/0 + 1*1*1 + 1*1*1 + 1*1*1 + 1, /*depv=*/NULL,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL_GUID);
		s3ComputeStep_dependencies(stepTag, edt_guid, context);
		return;
	}
	if(!strncmp(stepName, "kjiComputeStep\0", 14)){
		int k = getTag(stepTag, 0);
		int j = getTag(stepTag, 1);
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, kjiComputeStep_gets, 2, 0);
		void** args = (void**)cnc_malloc(2*sizeof(void*));
		args[0] = (void*) stepTag;
		args[1] = context;
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/2, /*paramv=*/(u64*)args,
			/*depc=*/0, /*depv=*/NULL,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL_GUID);
		kjiComputeStep_dependencies(stepTag, edt_guid, context);
		return;
	}
	if(!strncmp(stepName, "s1ComputeStep\0", 13)){
		int k = getTag(stepTag, 0);
		ocrGuid_t edt_guid, templ_guid;
		ocrEdtTemplateCreate(&templ_guid, s1ComputeStep_gets, 2, 0 + 1*1*1 + 1);
		void** args = (void**)cnc_malloc(2*sizeof(void*));
		args[0] = (void*) stepTag;
		args[1] = context;
		ocrEdtCreate(&edt_guid, templ_guid,
			/*paramc=*/2, /*paramv=*/(u64*)args,
			/*depc=*/0 + 1*1*1 + 1, /*depv=*/NULL,
			/*properties=*/0, /*affinity=*/0, /*outEvent=*/NULL_GUID);
		s1ComputeStep_dependencies(stepTag, edt_guid, context);
		return;
	}
	printf("Step %s not defined\n", stepName);
	assert(0);
}

