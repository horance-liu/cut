#ifndef H65272EEC_9259_408E_9121_253663AB9F98
#define H65272EEC_9259_408E_9121_253663AB9F98

#include <cum/core/matcher/decorator/Is.h>
#include <cum/core/def/ComparatorDef.h>

CUM_NS_BEGIN

namespace details
{
    template <typename T>
    Is<T>* is_implement(Matcher<T>* matcher, MatcherTag)
    {
        return new Is<T>(matcher);
    }

    template <typename T>
    Is<T>* is_implement(const T& expect, NotMatcherTag)
    {
        return new Is<T>(eq(expect));
    }
}

template <typename T>
Is<typename MatcherTraits<typename std::remove_pointer<T>::type>::argument>*
is(const T& expect)
{
    using matcher_type = typename std::remove_pointer<T>::type;
    return details::is_implement(expect, typename MatcherTraits<matcher_type>::category());
}

template <typename T>
Is<const T*>* is(const T expect[])
{
    return details::is_implement(expect, NotMatcherTag());
}

CUM_NS_END

#endif
