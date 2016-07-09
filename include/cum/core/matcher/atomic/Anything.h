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
    __OVERRIDE__(void describeTo(Description& description) const)
    {
        description.appendText(desc);
    }

    __OVERRIDE__(bool matches(const T&) const)
    {
        return true;
    }

    __OVERRIDE__(void describeMismatch(const T&, Description&) const)
    {}

private:
    std::string desc;
};

CUM_GENERIC_MATCHER_TAG(Anything);

CUM_NS_END

#endif
