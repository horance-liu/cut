#ifndef H65272EEC_9259_408E_9121_253663AB9F98
#define H65272EEC_9259_408E_9121_253663AB9F98

#include <hamcrest/core/matcher/decorator/Is.h>
#include <hamcrest/core/helper/CompartorHelper.h>

HAMCREST_NS_BEGIN

namespace details
{
    template <typename T>
    Is<typename T::argument_type> is_implement(const T& expect, MatcherTag)
    {
        return Is<typename T::argument_type>(expect);
    }

    template <typename T>
    Is<T> is_implement(const T& expect, NotMatcherTag)
    {
        return Is<T>(equal_to(expect));
    }
}

template <typename T>
Is<typename MatcherTraits<T>::argument> is(const T& expect)
{
    return details::is_implement(expect, typename MatcherTraits<T>::category());
}

template <typename T>
Is<const T*> is(const T expect[])
{
    return details::is_implement(expect, NotMatcherTag());
}

HAMCREST_NS_END

#endif
