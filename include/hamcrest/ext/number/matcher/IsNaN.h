#ifndef HE5C7BACC_C93E_4956_8696_1025674BD8CE
#define HE5C7BACC_C93E_4956_8696_1025674BD8CE

#include <hamcrest/internal/BaseMatcher.h>

HAMCREST_NS_BEGIN

struct IsNaN : BaseMatcher<double>
{
    OVERRIDE(const IsNaN* clone() const);
    OVERRIDE(bool matches(const double& actual) const);
    OVERRIDE(void describeTo(Description& desc) const);
};

HAMCREST_MATCHER_TAG(IsNaN, double);

HAMCREST_NS_END

#endif
