#include <hamcrest/helper/IsEqualHelper.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

TEST(is_equal, integer)
{
    ASSERT_THAT(0xFF, equal_to(0xFF));
    ASSERT_THAT(0xFFFF, equal_to(0xFFFF));
}

TEST(is_equal, bool)
{
    ASSERT_THAT(true, equal_to(true));
    ASSERT_THAT(false, equal_to(false));
}

TEST(is_equal, string)
{
    ASSERT_THAT("hello", equal_to("hello"));
    ASSERT_THAT("hello", equal_to(std::string("hello")));
    ASSERT_THAT(std::string("hello"), equal_to(std::string("hello")));
}
