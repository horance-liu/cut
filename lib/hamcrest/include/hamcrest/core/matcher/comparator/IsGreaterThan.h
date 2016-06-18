#ifndef _7LUN0OQGWD5RINSDM0GCZR7FFVZRXGD0P35557IOS8AGKBRMSSZ44LZC               
#define _7LUN0OQGWD5RINSDM0GCZR7FFVZRXGD0P35557IOS8AGKBRMSSZ44LZC

#include <hamcrest/core/matcher/comparator/Comparator.h>
#include <cub/algo/operator.h>

HAMCREST_NS_BEGIN

template <typename T>
struct IsGreaterThan : Comparator<T, std::greater<T>>
{
    explicit IsGreaterThan(const T& expected)
        : Comparator<T, std::greater<T>>("gt", expected)
    {}
};

template <>
struct IsGreaterThan<const char*> : Comparator<const char*, std::greater<const char*>>
{
    explicit IsGreaterThan(const char* const & expected)
        : Comparator<const char*, std::greater<const char*>>("gt", expected)
    {}
};

HAMCREST_GENERIC_MATCHER_TAG(IsGreaterThan);

HAMCREST_NS_END

#endif
