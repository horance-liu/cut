#include <hamcrest/ext/number/matcher/IsNaN.h>
#include <math.h>

HAMCREST_NS_BEGIN

bool IsNaN::matches(const double& actual) const
{
    return isnan(actual);
}

void IsNaN::describeTo(Description& desc) const
{
    desc.appendText("a double value of NaN");
}

HAMCREST_NS_END
