#include <hamcrest/ext/number/helper/IsNaNHelper.h>
#include <hamcrest/core/helper/IsHelper.h>
#include <hamcrest/core/helper/IsNotHelper.h>
#include <assertion/Asserter.h>
#include <math.h>

TEST(is_nan, double)
{
    ASSERT_THAT(sqrt(-1.0), not_a_number());
    ASSERT_THAT(sqrt(-1.0), is(not_a_number()));

    ASSERT_THAT(1.0/0.0,  is_not(not_a_number()));
    ASSERT_THAT(-1.0/0.0, is_not(not_a_number()));
}
