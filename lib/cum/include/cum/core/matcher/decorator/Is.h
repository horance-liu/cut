#ifndef HF1936DAE_CC46_49DE_A381_6206FE0D19C7
#define HF1936DAE_CC46_49DE_A381_6206FE0D19C7

#include <cum/internal/BaseMatcher.h>

CUM_NS_BEGIN

template <typename T>
struct Is : BaseMatcher<T>
{
    Is(Matcher<T>* matcher)
        : matcher(matcher)
    {}

    virtual ~Is()
    {
        delete matcher;
    }

private:
    OVERRIDE(bool matches(const T& actual) const)
    {
        return matcher->matches(actual);
    }

    OVERRIDE(void describeTo(Description& desc) const)
    {
        desc.appendText("is ").appendDescriptionOf(*matcher);
    }

    OVERRIDE(void describeMismatch(const T& actual, Description& dismatch) const)
    {
        matcher->describeMismatch(actual, dismatch);
    }

private:
    Matcher<T>* matcher;
};

CUM_GENERIC_MATCHER_TAG(Is);

CUM_NS_END

#endif
