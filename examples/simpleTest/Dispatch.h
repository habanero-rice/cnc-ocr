
   // ***** AUTO-GENERATED FILE FROM simpleTest.cnc, DO NOT MODIFY!  *****//

#ifndef _CNC_STEPS_H
#define _CNC_STEPS_H

#include "cnc_mm.h"
#include "Context.h"

#define Step_Step2 0
#define Step_Step1 1
#define Step_Step0 2

ocrGuid_t Step2_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]);
void Step2_dependencies(char * tag, ocrGuid_t edt_guid, Context * context);
ocrGuid_t Step1_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]);
void Step1_dependencies(char * tag, ocrGuid_t edt_guid, Context * context);
ocrGuid_t Step0_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]);
void Step0_dependencies(char * tag, ocrGuid_t edt_guid, Context * context);

#pragma hc continuable
void prescribeStep(char* stepName, char* stepTag, Context* context);


#endif /*_CNC_STEPS_H*/

