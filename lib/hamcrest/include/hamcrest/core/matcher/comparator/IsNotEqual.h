#ifndef H077CDC2B_EE2B_431F_89BE_F9EAE3061C3A
#define H077CDC2B_EE2B_431F_89BE_F9EAE3061C3A

#include "hamcrest/core/matcher/comparator/Comparator.h"
#include <cub/algo/operator.h>

HAMCREST_NS_BEGIN

template <typename T>
struct IsNotEqual : Comparator<T, std::not_equal_to<T>>
{
    explicit IsNotEqual(const T& expected)
        : Comparator<T, std::not_equal_to<T>>("ne", expected)
    {}
};

template <>
struct IsNotEqual<const char*> : Comparator<const char*, std::not_equal_to<const char*>>
{
    explicit IsNotEqual(const char* const & expected)
        : Comparator<const char*, std::not_equal_to<const char*>>("ne", expected)
    {}
};

HAMCREST_GENERIC_MATCHER_TAG(IsNotEqual);

HAMCREST_NS_END

#endif
