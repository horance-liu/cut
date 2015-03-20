#ifndef _7LUN0OQGWD5RINSDM0GCZR7FFVZRXGD0P35557IOS8AGKBRMSSZ44LZC               
#define _7LUN0OQGWD5RINSDM0GCZR7FFVZRXGD0P35557IOS8AGKBRMSSZ44LZC

#include "magellan/hamcrest/core/matcher/comparator/Comparator.h"

HAMCREST_NS_BEGIN

template <typename T>
struct IsGreaterThan : Comparator<T>
{
    explicit IsGreaterThan(const T& expected)
        : Comparator<T>("greater than", expected)
    {}

private:
    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new IsGreaterThan<T>(this->expected);
    }

    OVERRIDE(bool matches(const T& actual) const)
    {
        return actual > this->expected;
    }
};

HAMCREST_GENERIC_MATCHER_TAG(IsGreaterThan);

HAMCREST_NS_END

#endif
