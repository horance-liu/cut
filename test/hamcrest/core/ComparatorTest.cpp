#include <assertion/Asserter.h>
#include <hamcrest/core/helper/ComparatorHelper.h>
#include <hamcrest/core/helper/IsHelper.h>
#include <hamcrest/core/helper/IsNotHelper.h>

USING_HAMCREST_NS

TEST(equal_to, integer)
{
    ASSERT_THAT(0xFF, equal_to(0xFF));

    ASSERT_THAT(0xFF, is(0xFF));
    ASSERT_THAT(0xFF, is(equal_to(0xFF)));
    ASSERT_THAT(0xFF == 0xFF, is(true));
}

TEST(equal_to, bool)
{
    ASSERT_THAT(true, equal_to(true));
    ASSERT_THAT(false, equal_to(false));
}

TEST(equal_to, string)
{
    ASSERT_THAT("hello", equal_to("hello"));
    ASSERT_THAT("hello", equal_to(std::string("hello")));
    ASSERT_THAT(std::string("hello"), equal_to(std::string("hello")));
}

TEST(not_equal_to, integer)
{
    ASSERT_THAT(0xFF, not_equal_to(0xEE));

    ASSERT_THAT(0xFF, is_not(0xEE));
    ASSERT_THAT(0xFF, is_not(equal_to(0xEE)));
    ASSERT_THAT(0xFF != 0xEE, is(true));
}

TEST(not_equal_to, bool)
{
    ASSERT_THAT(true, not_equal_to(false));
    ASSERT_THAT(false, not_equal_to(true));
}

TEST(not_equal_to, string)
{
    ASSERT_THAT("hello", not_equal_to("world"));
    ASSERT_THAT("hello", not_equal_to(std::string("world")));
    ASSERT_THAT(std::string("hello"), not_equal_to(std::string("world")));
}

TEST(less_to, integer)
{
    ASSERT_THAT(0xEE, less_than(0xFF));
    ASSERT_THAT(0xEE, is(less_than(0xFF)));

    ASSERT_THAT(0xEE < 0xFF, is(true));
}

TEST(less_to, string)
{
    ASSERT_THAT("hello", less_than("world"));
    ASSERT_THAT("hello", less_than(std::string("world")));
    ASSERT_THAT(std::string("hello"), less_than(std::string("world")));
}

TEST(less_to_or_equal_to, integer)
{
    ASSERT_THAT(0xEE, less_than_or_equal_to(0xFF));
    ASSERT_THAT(0xEE, less_than_or_equal_to(0xEE));
}

TEST(less_to_or_equal_to, string)
{
    ASSERT_THAT("hello", less_than_or_equal_to("hello"));
    ASSERT_THAT("hello", less_than_or_equal_to(std::string("hello")));
    ASSERT_THAT(std::string("hello"), less_than_or_equal_to(std::string("hello")));

    ASSERT_THAT("hello", less_than_or_equal_to("world"));
    ASSERT_THAT("hello", less_than_or_equal_to(std::string("world")));
    ASSERT_THAT(std::string("hello"), less_than_or_equal_to(std::string("world")));
}

TEST(greater_than, integer)
{
    ASSERT_THAT(0xFF, greater_than(0xEE));
    ASSERT_THAT(0xFF, is(greater_than(0xEE)));
}

TEST(greater_than, string)
{
    ASSERT_THAT("world", greater_than("hello"));
    ASSERT_THAT("world", greater_than(std::string("hello")));
    ASSERT_THAT(std::string("world"), greater_than(std::string("hello")));
}

TEST(greater_than_or_equal_to, integer)
{
    ASSERT_THAT(0xFF, greater_than_or_equal_to(0xEE));
    ASSERT_THAT(0xFF, greater_than_or_equal_to(0xFF));
}

TEST(greater_than_or_equal_to, string)
{
    ASSERT_THAT("world", greater_than_or_equal_to("hello"));
    ASSERT_THAT("world", greater_than_or_equal_to(std::string("hello")));
    ASSERT_THAT(std::string("world"), greater_than_or_equal_to(std::string("hello")));

    ASSERT_THAT("world", greater_than_or_equal_to("world"));
    ASSERT_THAT("world", greater_than_or_equal_to(std::string("world")));
    ASSERT_THAT(std::string("world"), greater_than_or_equal_to(std::string("world")));
}
