#ifndef H5C3598B1_9AA4_4588_8D41_5AC3021257B1
#define H5C3598B1_9AA4_4588_8D41_5AC3021257B1

#include <cui/dci/__Role__.h>
#include <cum/cum.h>

CUM_NS_BEGIN

struct Description;

__TRAIT__(SelfDescribing)
{
    __ABSTRACT__(void describeTo(Description& desc) const);
};

CUM_NS_END

#endif

