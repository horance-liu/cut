#ifndef H8A4B6DA7_1106_4FA9_8422_86B8C81B4573
#define H8A4B6DA7_1106_4FA9_8422_86B8C81B4573

#include <std/stdext.h>

STDEXT_NS_BEGIN

template <typename C>
using iterator = typename C::iterator;

template <typename C>
using const_iterator = typename C::const_iterator;

template <typename T, size_t N>
inline constexpr size_t array_size(T(&)[N]) noexcept
{
    return N;
}

STDEXT_NS_END

#endif
