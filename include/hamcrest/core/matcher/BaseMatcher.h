#ifndef H51EBF108_EB0E_4847_BA80_3012AD037673
#define H51EBF108_EB0E_4847_BA80_3012AD037673

#include "hamcrest/base/Matcher.h"
#include "hamcrest/base/Description.h"

HAMCREST_NS_BEGIN

template <typename T>
GENERIC_ROLE(BaseMatcher) EXTENDS(Matcher<T>)
{
    OVERRIDE(void describeMismatch(const T* actual, Description& desc) const)
    {
        desc.appendText("was ").appendValue(actual);
    }
};

HAMCREST_NS_END

#endif
