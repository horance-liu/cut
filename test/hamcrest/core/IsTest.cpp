#include <gtest/gtest.h>
#include <hamcrest/helper/IsHelper.h>
#include <hamcrest/core/IsNil.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

TEST(is, integer)
{
    ASSERT_THAT(0xff, is(0xFF));
    ASSERT_THAT(0xff, is(equal_to(0xFF)));
}

TEST(is, bool)
{
    ASSERT_THAT(true, is(true));
    ASSERT_THAT(false, is(false));
}

TEST(is, string)
{
    ASSERT_THAT("hello", is("hello"));
    ASSERT_THAT("hello", is(equal_to("hello")));

    ASSERT_THAT("hello", is(std::string("hello")));
    ASSERT_THAT(std::string("hello"), is(std::string("hello")));
}
