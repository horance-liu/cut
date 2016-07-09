#ifndef _8NT1GNZJHQJIDQ5CHOBNEIYHQTXDU89K6T7OBWJQSOP4MXLC8DN3Z4KY               
#define _8NT1GNZJHQJIDQ5CHOBNEIYHQTXDU89K6T7OBWJQSOP4MXLC8DN3Z4KY

#include <cui/algo/__operator__.h>
#include <cum/core/matcher/comparator/Comparator.h>

CUM_NS_BEGIN

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

CUM_GENERIC_MATCHER_TAG(IsLessThanOrEqualTo);

CUM_NS_END

#endif
