#ifndef _1DL9WARF4DOY7XLWH9ZNA67ERN4VYAJUBKSSMJQ25C9VXNK58DWGHD1               
#define _1DL9WARF4DOY7XLWH9ZNA67ERN4VYAJUBKSSMJQ25C9VXNK58DWGHD1

#include "hamcrest/core/matcher/comparator/Comparator.h"
#include <cub/algo/operator.h>

HAMCREST_NS_BEGIN

template <typename T>
struct IsGreaterThanOrEqualTo : Comparator<T, std::greater_equal<T>>
{
    explicit IsGreaterThanOrEqualTo(const T& expected)
        : Comparator<T, std::greater_equal<T>>("ge", expected)
    {}
};

template <>
struct IsGreaterThanOrEqualTo<const char*> : Comparator<const char*, std::greater_equal<const char*>>
{
    explicit IsGreaterThanOrEqualTo(const char* const & expected)
        : Comparator<const char*, std::greater_equal<const char*>>("ge", expected)
    {}
};

HAMCREST_GENERIC_MATCHER_TAG(IsGreaterThanOrEqualTo);

HAMCREST_NS_END


#endif
