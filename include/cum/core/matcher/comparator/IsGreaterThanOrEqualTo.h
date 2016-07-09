#ifndef _1DL9WARF4DOY7XLWH9ZNA67ERN4VYAJUBKSSMJQ25C9VXNK58DWGHD1               
#define _1DL9WARF4DOY7XLWH9ZNA67ERN4VYAJUBKSSMJQ25C9VXNK58DWGHD1

#include <cui/algo/__operator__.h>
#include <cum/core/matcher/comparator/Comparator.h>

CUM_NS_BEGIN

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

CUM_GENERIC_MATCHER_TAG(IsGreaterThanOrEqualTo);

CUM_NS_END


#endif
