#ifndef H3D00A295_D9EA_479A_AAA0_2FDBA1AE5389
#define H3D00A295_D9EA_479A_AAA0_2FDBA1AE5389

#include <hamcrest/internal/BaseMatcher.h>

HAMCREST_NS_BEGIN

template <typename T>
struct Anything : BaseMatcher<T>
{
    Anything(const std::string& desc = "anything")
        : desc(desc)
    {}

private:
    OVERRIDE(void describeTo(Description& description) const)
    {
        description.appendText(desc);
    }

    OVERRIDE(bool matches(const T&) const)
    {
        return true;
    }

    OVERRIDE(void describeMismatch(const T&, Description&) const)
    {}

private:
    std::string desc;
};

HAMCREST_GENERIC_MATCHER_TAG(Anything);

HAMCREST_NS_END

#endif
