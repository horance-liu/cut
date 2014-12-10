#ifndef H97BCD1FA_2A90_4110_BD1A_D6E7A1004220
#define H97BCD1FA_2A90_4110_BD1A_D6E7A1004220

#include <hamcrest/core/Description.h>
#include <hamcrest/core/SelfDescribing.h>

HAMCREST_NS_BEGIN

template <typename T>
struct SelfDescribingValue : SelfDescribing
{
    typedef T value_type;

    explicit SelfDescribingValue(const T& value) : value(value)
    {}

private:
    OVERRIDE(void describeTo(Description& desc) const)
    {
        desc.appendValue(value);
    }

private:
    T value;
};

HAMCREST_NS_END

#endif
