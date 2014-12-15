#include <hamcrest/core/helper/IsHelper.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

TEST(is, integer)
{
    ASSERT_THAT(0xff, is(0xFF));
    ASSERT_THAT(0xff, is(equal_to(0xFF)));
}

namespace
{
    bool should_be_true()
    {
        return true;
    }

    bool should_be_false()
    {
        return false;
    }
}

TEST(is, bool)
{
    ASSERT_THAT(should_be_true(),  is(true));
    ASSERT_THAT(should_be_false(), is(false));

    ASSERT_THAT(should_be_true(),  is(equal_to(true)));
    ASSERT_THAT(should_be_false(), is(equal_to(false)));
}

TEST(is, string)
{
    ASSERT_THAT("hello", is("hello"));
    ASSERT_THAT("hello", is(equal_to("hello")));

    ASSERT_THAT("hello", is(std::string("hello")));
    ASSERT_THAT(std::string("hello"), is(std::string("hello")));
}
