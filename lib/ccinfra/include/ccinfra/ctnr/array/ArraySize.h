#ifndef H29B1191B_457B_4E80_8056_4573626F0A98
#define H29B1191B_457B_4E80_8056_4573626F0A98

#include <ccinfra/base/BaseTypes.h>

CCINFRA_NS_BEGIN

#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

template <class T, size_t N>
inline T* begin_a(T(&arr)[N])
{
    return arr;
}

template <class T, size_t N>
inline T* end_a(T(&arr)[N])
{
    return arr + N;
}

template <class T, size_t N>
inline size_t length(T(&arr)[N])
{
    return N;
}

template <class T, size_t N>
inline size_t position(T(&arr)[N], const T* p)
{
    return p - arr;
}

CCINFRA_NS_END

#endif
