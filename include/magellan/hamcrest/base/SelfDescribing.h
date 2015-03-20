#ifndef H5C3598B1_9AA4_4588_8D41_5AC3021257B1
#define H5C3598B1_9AA4_4588_8D41_5AC3021257B1

#include <magellan/hamcrest/base/hamcrest.h>
#include <magellan/infra/dci/Role.h>

HAMCREST_NS_BEGIN

struct Description;

DEFINE_ROLE(SelfDescribing)
{
    ABSTRACT(void describeTo(Description& desc) const);
};

HAMCREST_NS_END

#endif

