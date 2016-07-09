#ifndef _7LUN0OQGWD5RINSDM0GCZR7FFVZRXGD0P35557IOS8AGKBRMSSZ44LZC               
#define _7LUN0OQGWD5RINSDM0GCZR7FFVZRXGD0P35557IOS8AGKBRMSSZ44LZC

#include <cui/algo/__operator__.h>
#include <cum/core/matcher/comparator/Comparator.h>

CUM_NS_BEGIN

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

CUM_GENERIC_MATCHER_TAG(IsGreaterThan);

CUM_NS_END

#endif
