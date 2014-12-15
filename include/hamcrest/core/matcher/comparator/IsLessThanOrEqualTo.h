#ifndef _8NT1GNZJHQJIDQ5CHOBNEIYHQTXDU89K6T7OBWJQSOP4MXLC8DN3Z4KY               
#define _8NT1GNZJHQJIDQ5CHOBNEIYHQTXDU89K6T7OBWJQSOP4MXLC8DN3Z4KY

#include "hamcrest/core/matcher/comparator/Comparator.h"

HAMCREST_NS_BEGIN

template <typename T>
struct IsLessThanOrEqualTo : Comparator<T>
{
    explicit IsLessThanOrEqualTo(const T& expected)
        : Comparator<T>("less than or equal to", expected)
    {}

private:
    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new IsLessThanOrEqualTo<T>(this->expected);
    }

    OVERRIDE(bool matches(const T& actual) const)
    {
        return actual <= this->expected;
    }
};

HAMCREST_GENERIC_MATCHER_TAG(IsLessThanOrEqualTo);

HAMCREST_NS_END

#endif
