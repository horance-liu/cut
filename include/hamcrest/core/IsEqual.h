#ifndef H269B7CCF_AE6C_49D4_AEF4_F72B7B3F545B
#define H269B7CCF_AE6C_49D4_AEF4_F72B7B3F545B

#include "hamcrest/base/BaseMatcher.h"

HAMCREST_NS_BEGIN

template <typename T>
struct IsEqual : BaseMatcher<T>
{
    explicit IsEqual(const T& expected)
        : expected(expected)
    {}

    virtual ~IsEqual() = default;

private:
    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new IsEqual<T>(expected);
    }

    OVERRIDE(bool matches(const T& actual) const)
    {
        return actual == expected;
    }

    OVERRIDE(void describeTo(Description& desc) const)
    {
        desc.appendValue(expected);
    }

private:
    const T expected;
};

HAMCREST_GENERIC_MATCHER_TAG(IsEqual);

HAMCREST_NS_END

#endif
