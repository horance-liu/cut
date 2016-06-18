#ifndef H5712E60C_DEF5_4A3B_93C0_C074CD80C63B
#define H5712E60C_DEF5_4A3B_93C0_C074CD80C63B

#include <ccinfra/ccinfra.h>
#include <ccinfra/base/BaseTypes.h>

CCINFRA_NS_BEGIN

typedef U32 Status;

const U16 INVALID_U16 = 0xFFFF;
const U32 INVALID_U32 = 0xFFFFFFFF;

const Status CCINFRA_SUCCESS = 0;
const Status CCINFRA_FAILURE = INVALID_U32;

#define __CCINFRA_FAILED(result)  (result != CCINFRA_SUCCESS)
#define __CCINFRA_SUCCESS(result)  (result == CCINFRA_SUCCESS)

CCINFRA_NS_END

#endif
