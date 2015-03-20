#ifndef H269B7CCF_AE6C_49D4_AEF4_F72B7B3F545B
#define H269B7CCF_AE6C_49D4_AEF4_F72B7B3F545B

#include "magellan/hamcrest/core/matcher/comparator/Comparator.h"

HAMCREST_NS_BEGIN

template <typename T>
struct IsEqual : Comparator<T>
{
    explicit IsEqual(const T& expected)
        : Comparator<T>("equal to", expected)
    {}

private:
    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new IsEqual<T>(this->expected);
    }

    OVERRIDE(bool matches(const T& actual) const)
    {
        return actual == this->expected;
    }
};

HAMCREST_GENERIC_MATCHER_TAG(IsEqual);

HAMCREST_NS_END

#endif
