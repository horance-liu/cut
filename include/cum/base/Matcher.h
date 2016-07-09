#ifndef H20D1811C_DB7E_4401_803C_98BA018ECCCB
#define H20D1811C_DB7E_4401_803C_98BA018ECCCB

#include <cum/base/SelfDescribing.h>
#include <cum/base/MatcherTraits.h>
#include <functional>

CUM_NS_BEGIN

struct Description;

template <typename T>
struct Matcher : SelfDescribing
{
    using argument_type = T;

    __ABSTRACT__(bool matches(const T& actual) const);
    __ABSTRACT__(void describeMismatch(const T& actual, Description& mismatch) const);
};

CUM_NS_END

#endif
