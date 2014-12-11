#include <hamcrest/ext/number/helper/IsCloseToHelper.h>
#include <assertion/Asserter.h>
#include <algorithm>

USING_HAMCREST_NS

TEST(close_to, double)
{
    ASSERT_THAT(1.0, close_to(1.0, 0.5));
    ASSERT_THAT(0.5, close_to(1.0, 0.5));
    ASSERT_THAT(1.5, close_to(1.0, 0.5));
}

TEST(close_to, float)
{
    ASSERT_THAT(1.0f, close_to(1.0, 0.5f));
    ASSERT_THAT(0.5f, close_to(1.0f, 0.5));
    ASSERT_THAT(1.5f, close_to(1.0f, 0.5f));
}

TEST(close_to, long_double)
{
    ASSERT_THAT(1.0L, close_to(1.0, 0.5));
    ASSERT_THAT(0.5L, close_to(1.0, 0.5L));
    ASSERT_THAT(1.5L, close_to(1.0L, 0.5L));
}
