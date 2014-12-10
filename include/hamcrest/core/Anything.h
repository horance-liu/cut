#ifndef H3D00A295_D9EA_479A_AAA0_2FDBA1AE5389
#define H3D00A295_D9EA_479A_AAA0_2FDBA1AE5389

#include <hamcrest/base/BaseMatcher.h>

HAMCREST_NS_BEGIN

template <typename T>
struct anything : BaseMatcher<T>
{
    anything(const std::string& desc = "ANYTHING")
        : desc(desc)
    {}

    virtual ~anything() = default;

private:
    OVERRIDE(void describeTo(Description& description) const)
    {
        description.appendText(desc);
    }

    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new anything(*this);
    }

    OVERRIDE(bool matches(const T&) const)
    {
        return true;
    }

    OVERRIDE(void describeMismatch(const T&, Description&) const) {}

private:
    std::string desc;
};

HAMCREST_GENERIC_MATCHER_TAG(anything);

HAMCREST_NS_END

#endif
