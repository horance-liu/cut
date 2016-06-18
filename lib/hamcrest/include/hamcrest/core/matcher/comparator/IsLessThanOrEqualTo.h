#ifndef _8NT1GNZJHQJIDQ5CHOBNEIYHQTXDU89K6T7OBWJQSOP4MXLC8DN3Z4KY               
#define _8NT1GNZJHQJIDQ5CHOBNEIYHQTXDU89K6T7OBWJQSOP4MXLC8DN3Z4KY

#include <hamcrest/core/matcher/comparator/Comparator.h>
#include <cub/algo/operator.h>

HAMCREST_NS_BEGIN

template <typename T>
struct IsLessThanOrEqualTo : Comparator<T, std::less_equal<T>>
{
    explicit IsLessThanOrEqualTo(const T& expected)
        : Comparator<T, std::less_equal<T>>("le", expected)
    {}
};

template <>
struct IsLessThanOrEqualTo<const char*> : Comparator<const char*, std::less_equal<const char*>>
{
    explicit IsLessThanOrEqualTo(const char* const & expected)
        : Comparator<const char*, std::less_equal<const char*>>("le", expected)
    {}
};

HAMCREST_GENERIC_MATCHER_TAG(IsLessThanOrEqualTo);

HAMCREST_NS_END

#endif
