#ifndef _1DL9WARF4DOY7XLWH9ZNA67ERN4VYAJUBKSSMJQ25C9VXNK58DWGHD1               
#define _1DL9WARF4DOY7XLWH9ZNA67ERN4VYAJUBKSSMJQ25C9VXNK58DWGHD1

#include "hamcrest/core/matcher/comparator/Comparator.h"

HAMCREST_NS_BEGIN

template <typename T>
struct IsGreaterThanOrEqualTo : Comparator<T>
{
    explicit IsGreaterThanOrEqualTo(const T& expected)
        : Comparator<T>("greater than or equal to", expected)
    {}

private:
    OVERRIDE(const Matcher<T>* clone() const)
    {
        return new IsGreaterThanOrEqualTo<T>(this->expected);
    }

    OVERRIDE(bool matches(const T& actual) const)
    {
        return actual >= this->expected;
    }
};

HAMCREST_GENERIC_MATCHER_TAG(IsGreaterThanOrEqualTo);

HAMCREST_NS_END


#endif
