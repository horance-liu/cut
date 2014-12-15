#ifndef H1368FCA0_5942_44AD_8C3E_29AF182FF6BF
#define H1368FCA0_5942_44AD_8C3E_29AF182FF6BF

#include "hamcrest/internal/BaseMatcher.h"

HAMCREST_NS_BEGIN

template <typename T>
struct IsNot : BaseMatcher<T>
{
    explicit IsNot(const Matcher<T>& matcher)
        : matcher(matcher.clone())
    {}

    virtual ~IsNot()
    {
        delete matcher;
    }

private:
    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new IsNot<T>(*matcher);
    }

    OVERRIDE(bool matches(const T& actual) const)
    {
        return !(matcher->matches(actual));
    }

    OVERRIDE(void describeTo(Description& desc) const)
    {
        desc.appendText("is not ").appendDescriptionOf(*matcher);
    }

private:
    const Matcher<T> *matcher;
};

HAMCREST_GENERIC_MATCHER_TAG(IsNot);

HAMCREST_NS_END

#endif
