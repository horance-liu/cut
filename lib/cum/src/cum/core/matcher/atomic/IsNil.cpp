#include <cum/core/matcher/atomic/IsNil.h>

CUM_NS_BEGIN

bool IsNil::matches(const void* const& actual) const
{
    return actual == nullptr;
}

void IsNil::describeTo(Description& desc) const
{
    desc.appendValue("nil pointer");
}

CUM_NS_END
