#ifndef H1368FCA0_5942_44AD_8C3E_29AF182FF6BF
#define H1368FCA0_5942_44AD_8C3E_29AF182FF6BF

#include <cum/internal/BaseMatcher.h>

CUM_NS_BEGIN

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
    __OVERRIDE__(bool matches(const T& actual) const)
    {
        return !(matcher->matches(actual));
    }

    __OVERRIDE__(void describeTo(Description& desc) const)
    {
        desc.appendText("is not ").appendDescriptionOf(*matcher);
    }

private:
    Matcher<T>* matcher;
};

CUM_GENERIC_MATCHER_TAG(IsNot);

CUM_NS_END

#endif
