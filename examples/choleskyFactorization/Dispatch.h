
   // ***** AUTO-GENERATED FILE FROM Cholesky.cnc, DO NOT MODIFY!  *****//

#ifndef _CNC_STEPS_H
#define _CNC_STEPS_H

#include "cnc_mm.h"
#include "Context.h"

#define Step_kComputeStep 0
#define Step_s2ComputeStep 1
#define Step_kjComputeStep 2
#define Step_s3ComputeStep 3
#define Step_kjiComputeStep 4
#define Step_s1ComputeStep 5

ocrGuid_t kComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]);
void kComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context);
ocrGuid_t s2ComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]);
void s2ComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context);
ocrGuid_t kjComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]);
void kjComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context);
ocrGuid_t s3ComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]);
void s3ComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context);
ocrGuid_t kjiComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]);
void kjiComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context);
ocrGuid_t s1ComputeStep_gets(u32 paramc, u64 * paramv, u32 depc, ocrEdtDep_t depv[]);
void s1ComputeStep_dependencies(char * tag, ocrGuid_t edt_guid, Context * context);

#pragma hc continuable
void prescribeStep(char* stepName, char* stepTag, Context* context);


#endif /*_CNC_STEPS_H*/

