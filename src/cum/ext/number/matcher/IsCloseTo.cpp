#include <cum/ext/number/matcher/IsCloseTo.h>

CUM_NS_BEGIN

namespace
{
    long double abs_d(long double a)
    {
        return (a <= 0.0) ? 0.0 - a : a;
    }
}

long double IsCloseTo::actualDelta(long double item) const
{
    return abs_d(item - value) - delta;
}

IsCloseTo::IsCloseTo(long double value, long double delta)
    : value(value), delta(delta)
{
}

bool IsCloseTo::matches(const long double& actual) const
{
    return actualDelta(actual) <= 0.0;
}

void IsCloseTo::describeTo(Description& desc) const
{
    desc.appendText("a numeric value within ")
        .appendValue(delta)
        .appendText(" of ")
        .appendValue(value);
}

void IsCloseTo::describeMismatch(const long double& actual, Description& mismatch) const
{
    mismatch.appendValue(actual)
            .appendText(" differed by ")
            .appendValue(actualDelta(actual))
            .appendText(" more than delta ")
            .appendValue(delta);
}

CUM_NS_END
