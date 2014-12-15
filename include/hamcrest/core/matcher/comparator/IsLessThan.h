#ifndef _UYLLGSZTJHPGMMFF1H269RIPLKIUOIZDCM6CCXZHMF3ILFT7M69YYX0P               
#define _UYLLGSZTJHPGMMFF1H269RIPLKIUOIZDCM6CCXZHMF3ILFT7M69YYX0P

#include "hamcrest/core/matcher/comparator/Comparator.h"

HAMCREST_NS_BEGIN

template <typename T>
struct IsLessThan : Comparator<T>
{
    explicit IsLessThan(const T& expected)
        : Comparator<T>("less than", expected)
    {}

private:
    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new IsLessThan<T>(this->expected);
    }

    OVERRIDE(bool matches(const T& actual) const)
    {
        return actual < this->expected;
    }
};

HAMCREST_GENERIC_MATCHER_TAG(IsLessThan);

HAMCREST_NS_END

#endif
