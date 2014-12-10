#ifndef HCAB75B4B_8F10_461E_9087_04A4AC719FAF
#define HCAB75B4B_8F10_461E_9087_04A4AC719FAF

#include <hamcrest/base/BaseMatcher.h>

HAMCREST_NS_BEGIN

struct IsNil : BaseMatcher<const void*>
{
    OVERRIDE(const IsNil* clone() const);
    OVERRIDE(bool matches(const void* const& actual) const);
    OVERRIDE(void describeTo(Description& desc) const);
};

HAMCREST_MATCHER_TAG(IsNil, const void*);

HAMCREST_NS_END

#endif
