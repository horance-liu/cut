#include <hamcrest/core/matcher/atomic/IsNil.h>

HAMCREST_NS_BEGIN

bool IsNil::matches(const void* const& actual) const
{
    return actual == nullptr;
}

void IsNil::describeTo(Description& desc) const
{
    desc.appendValue("nil pointer");
}

HAMCREST_NS_END
