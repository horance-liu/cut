#ifndef H077CDC2B_EE2B_431F_89BE_F9EAE3061C3A
#define H077CDC2B_EE2B_431F_89BE_F9EAE3061C3A

#include "hamcrest/core/matcher/comparator/Comparator.h"

HAMCREST_NS_BEGIN

template <typename T>
struct IsNotEqual : Comparator<T>
{
    explicit IsNotEqual(const T& expected)
        : Comparator<T>("not equal to", expected)
    {}

private:
    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new IsNotEqual<T>(this->expected);
    }

    OVERRIDE(bool matches(const T& actual) const)
    {
        return !(actual == this->expected);
    }
};

HAMCREST_GENERIC_MATCHER_TAG(IsNotEqual);

HAMCREST_NS_END

#endif
