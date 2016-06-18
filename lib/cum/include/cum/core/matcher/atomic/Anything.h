#ifndef H3D00A295_D9EA_479A_AAA0_2FDBA1AE5389
#define H3D00A295_D9EA_479A_AAA0_2FDBA1AE5389

#include <cum/internal/BaseMatcher.h>

CUM_NS_BEGIN

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

CUM_GENERIC_MATCHER_TAG(Anything);

CUM_NS_END

#endif
