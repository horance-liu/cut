#ifndef H1368FCA0_5942_44AD_8C3E_29AF182FF6BF
#define H1368FCA0_5942_44AD_8C3E_29AF182FF6BF

#include <hamcrest/internal/BaseMatcher.h>

HAMCREST_NS_BEGIN

template <typename T>
struct IsNot : BaseMatcher<T>
{
    explicit IsNot(Matcher<T>* matcher)
        : matcher(matcher)
    {}

    virtual ~IsNot()
    {
        delete matcher;
    }

private:
    OVERRIDE(bool matches(const T& actual) const)
    {
        return !(matcher->matches(actual));
    }

    OVERRIDE(void describeTo(Description& desc) const)
    {
        desc.appendText("is not ").appendDescriptionOf(*matcher);
    }

private:
    Matcher<T>* matcher;
};

HAMCREST_GENERIC_MATCHER_TAG(IsNot);

HAMCREST_NS_END

#endif
