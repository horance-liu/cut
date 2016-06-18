#ifndef HE5C7BACC_C93E_4956_8696_1025674BD8CE
#define HE5C7BACC_C93E_4956_8696_1025674BD8CE

#include <cum/internal/BaseMatcher.h>

CUM_NS_BEGIN

struct IsNaN : BaseMatcher<double>
{
    OVERRIDE(bool matches(const double& actual) const);
    OVERRIDE(void describeTo(Description& desc) const);
};

CUM_MATCHER_TAG(IsNaN, double);

CUM_NS_END

#endif
