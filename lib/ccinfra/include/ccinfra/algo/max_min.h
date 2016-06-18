#ifndef H1BEBC79D_5BA8_1123_AD8C_94F820EC7D5B
#define H1BEBC79D_5BA8_1123_AD8C_94F820EC7D5B

#include <ccinfra/ccinfra.h>
#include <ccinfra/base/BaseTypes.h>
#include <algorithm>

CCINFRA_NS_BEGIN

#define __MIN(a,b)    std::min(a, b)
#define __MAX(a,b)    std::max(a, b)

#define __BETWEEN(v, min, max) __MAX((min), __MIN((v), (max)))

template <typename T, T MIN_VALUE, T MAX_VALUE>
struct ValueScope
{
	static T fix(const T value)
	{
		return std::max(MIN_VALUE, std::min(MAX_VALUE, value));
	}
};

template <typename T, T MIN, T MAX>
inline T __between(const T value)
{
	return ValueScope<T, MIN, MAX>::convert(value);
}

template <U8 MIN, U8 MAX>
inline U8 between(const U8 value)
{
	return __between<U8, MIN, MAX>(value);
}

template <typename T, T MIN, T MAX>
inline bool __isBetween(const T value)
{
    return (value >= MIN) && (value <= MAX);
}

template <U8 MIN, U8 MAX>
inline bool isBetween(const U8 value)
{
    return __isBetween<U8, MIN, MAX>(value);
}

CCINFRA_NS_END

#endif
