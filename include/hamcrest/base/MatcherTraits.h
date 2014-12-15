#ifndef HAC0ECC9C_2787_410E_8B4E_9A89458BA795
#define HAC0ECC9C_2787_410E_8B4E_9A89458BA795

#include <hamcrest/base/hamcrest.h>

HAMCREST_NS_BEGIN

struct NotMatcherTag {};
struct MatcherTag    {};

template <typename T>
struct MatcherTraits
{
    using argument = T;
    using category = NotMatcherTag;
};

#define HAMCREST_MATCHER_TAG(matcher_t, arg_t) \
    template <>                                   \
    struct MatcherTraits< matcher_t >             \
    {                                             \
        using argument = arg_t;                   \
        using category = MatcherTag;              \
    }

#define HAMCREST_GENERIC_MATCHER_TAG(matcher_t)  \
    template <typename T>                        \
    struct MatcherTraits< matcher_t<T> >         \
    {                                            \
        using argument = T;                      \
        using category = MatcherTag;             \
    }

HAMCREST_NS_END

#endif
