#include <hamcrest/core/helper/IsNotHelper.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

TEST(is_not, integer)
{
    ASSERT_THAT(0xFF, is_not(0xEE));
    ASSERT_THAT(0xFF, is_not(equal_to(0xEE)));
}

TEST(is_not, string)
{
    ASSERT_THAT("hello", is_not("world"));
    ASSERT_THAT("hello", is_not(equal_to("world")));

    ASSERT_THAT("hello", is_not(std::string("world")));
    ASSERT_THAT(std::string("hello"), is_not(std::string("world")));
}
