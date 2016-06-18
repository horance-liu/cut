#ifndef _UYLLGSZTJHPGMMFF1H269RIPLKIUOIZDCM6CCXZHMF3ILFT7M69YYX0P               
#define _UYLLGSZTJHPGMMFF1H269RIPLKIUOIZDCM6CCXZHMF3ILFT7M69YYX0P

#include "hamcrest/core/matcher/comparator/Comparator.h"
#include <cub/algo/operator.h>

HAMCREST_NS_BEGIN

template <typename T>
struct IsLessThan : Comparator<T, std::less<T>>
{
    explicit IsLessThan(const T& expected)
        : Comparator<T, std::less<T>>("lt", expected)
    {}
};

template <>
struct IsLessThan<const char*> : Comparator<const char*, std::less<const char*>>
{
    explicit IsLessThan(const char* const & expected)
        : Comparator<const char*, std::less<const char*>>("lt", expected)
    {}
};

HAMCREST_GENERIC_MATCHER_TAG(IsLessThan);

HAMCREST_NS_END

#endif
