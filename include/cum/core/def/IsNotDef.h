#ifndef H6FE7D00B_4D0D_419D_A21A_1C4243288223
#define H6FE7D00B_4D0D_419D_A21A_1C4243288223

#include <cum/core/matcher/decorator/IsNot.h>
#include <cum/core/def/ComparatorDef.h>

CUM_NS_BEGIN

namespace details
{
    template <typename T>
    IsNot<T>* is_not_implement(Matcher<T>* matcher, MatcherTag)
    {
        return new IsNot<T>(matcher);
    }

    template <typename T>
    IsNot<T>* is_not_implement(const T& expect, NotMatcherTag)
    {
        return new IsNot<T>(eq(expect));
    }
}

template <typename T>
IsNot<typename MatcherTraits<typename std::remove_pointer<T>::type>::argument>*
is_not(const T& expect)
{
    using matcher_type = typename std::remove_pointer<T>::type;
    return details::is_not_implement(expect, typename MatcherTraits<matcher_type>::category());
}

template <typename T>
IsNot<const T*>* is_not(const T expect[])
{
    return details::is_not_implement(expect, NotMatcherTag());
}

CUM_NS_END

#endif
