#ifndef H6FE7D00B_4D0D_419D_A21A_1C4243288223
#define H6FE7D00B_4D0D_419D_A21A_1C4243288223

#include <hamcrest/core/matcher/decorator/IsNot.h>
#include <hamcrest/core/helper/ComparatorHelper.h>

HAMCREST_NS_BEGIN

namespace details
{
    template <typename T>
    IsNot<typename T::argument_type> is_not_implement(const T& expect, MatcherTag)
    {
        return IsNot<typename T::argument_type>(expect);
    }

    template <typename T>
    IsNot<T> is_not_implement(const T& expect, NotMatcherTag)
    {
        return IsNot<T>(equal_to(expect));
    }
}

template <typename T>
IsNot<typename MatcherTraits<T>::argument> is_not(const T& expect)
{
    return details::is_not_implement(expect, typename MatcherTraits<T>::category());
}

template <typename T>
IsNot<const T*> is_not(const T expect[])
{
    return details::is_not_implement(expect, NotMatcherTag());
}

HAMCREST_NS_END

#endif
