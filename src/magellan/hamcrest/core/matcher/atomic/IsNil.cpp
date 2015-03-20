#include <magellan/hamcrest/core/matcher/atomic/IsNil.h>

HAMCREST_NS_BEGIN

const IsNil* IsNil::clone() const
{
    return new IsNil;
}

bool IsNil::matches(const void* const& actual) const
{
    return actual == nullptr;
}

void IsNil::describeTo(Description& desc) const
{
    desc.appendValue("nullptr");
}

HAMCREST_NS_END
