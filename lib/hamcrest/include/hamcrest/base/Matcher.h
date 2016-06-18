#ifndef H20D1811C_DB7E_4401_803C_98BA018ECCCB
#define H20D1811C_DB7E_4401_803C_98BA018ECCCB

#include <hamcrest/base/SelfDescribing.h>
#include <hamcrest/base/MatcherTraits.h>
#include <functional>

HAMCREST_NS_BEGIN

struct Description;

template <typename T>
struct Matcher : SelfDescribing
{
    using argument_type = T;

    ABSTRACT(bool matches(const T& actual) const);
    ABSTRACT(void describeMismatch(const T& actual, Description& mismatch) const);
};

HAMCREST_NS_END

#endif
