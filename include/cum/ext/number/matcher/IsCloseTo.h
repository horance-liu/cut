#ifndef H8470FF6C_251A_4176_8AC3_6EE17C0EC20B
#define H8470FF6C_251A_4176_8AC3_6EE17C0EC20B

#include <cum/internal/BaseMatcher.h>

CUM_NS_BEGIN

struct IsCloseTo : BaseMatcher<long double>
{
    IsCloseTo(long double value, long double delta);

private:
    __OVERRIDE__(bool matches(const long double& actual) const);
    __OVERRIDE__(void describeTo(Description& desc) const);
    __OVERRIDE__(void describeMismatch(const long double&, Description&) const);

private:
    long double actualDelta(long double item) const;

private:
    const long double value;
    const long double delta;
};

CUM_MATCHER_TAG(IsCloseTo, long double);

CUM_NS_END

#endif
