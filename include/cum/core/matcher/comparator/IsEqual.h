#ifndef H269B7CCF_AE6C_49D4_AEF4_F72B7B3F545B
#define H269B7CCF_AE6C_49D4_AEF4_F72B7B3F545B

#include <cui/algo/__operator__.h>
#include <cum/core/matcher/comparator/Comparator.h>

CUM_NS_BEGIN

template <typename T>
struct IsEqual : Comparator<T, std::equal_to<T>>
{
    explicit IsEqual(const T& expected)
        : Comparator<T, std::equal_to<T>>("eq", expected)
    {}
};

template <>
struct IsEqual<const char*> : Comparator<const char*, std::equal_to<const char*>>
{
    explicit IsEqual(const char* const & expected)
        : Comparator<const char*, std::equal_to<const char*>>("eq", expected)
    {}
};

CUM_GENERIC_MATCHER_TAG(IsEqual);

CUM_NS_END

#endif
