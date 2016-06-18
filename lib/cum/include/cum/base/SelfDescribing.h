#ifndef H5C3598B1_9AA4_4588_8D41_5AC3021257B1
#define H5C3598B1_9AA4_4588_8D41_5AC3021257B1

#include <cum/cum.h>
#include <cub/dci/Role.h>

CUM_NS_BEGIN

struct Description;

DEFINE_ROLE(SelfDescribing)
{
    ABSTRACT(void describeTo(Description& desc) const);
};

CUM_NS_END

#endif

