#ifndef H51EBF108_EB0E_4847_BA80_3012AD037673
#define H51EBF108_EB0E_4847_BA80_3012AD037673

#include <cum/base/Matcher.h>
#include <cum/base/Description.h>

CUM_NS_BEGIN

template <typename T>
struct BaseMatcher : Matcher<T>
{
private:
    __OVERRIDE__(void describeMismatch(const T& actual, Description& desc) const)
    {
        desc.appendText("was ").appendValue(actual);
    }
};

CUM_NS_END

#endif
