#ifndef H8470FF6C_251A_4176_8AC3_6EE17C0EC20B
#define H8470FF6C_251A_4176_8AC3_6EE17C0EC20B

#include <hamcrest/internal/BaseMatcher.h>

HAMCREST_NS_BEGIN

struct IsCloseTo : BaseMatcher<long double>
{
    IsCloseTo(long double value, long double delta);

private:
    OVERRIDE(bool matches(const long double& actual) const);
    OVERRIDE(void describeTo(Description& desc) const);
    OVERRIDE(void describeMismatch(const long double&, Description&) const);

private:
    long double actualDelta(long double item) const;

private:
    const long double value;
    const long double delta;
};

HAMCREST_MATCHER_TAG(IsCloseTo, long double);

HAMCREST_NS_END

#endif
