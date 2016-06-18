#include <hamcrest/core/def/IsNotDef.h>
#include <magellan/magellan.hpp>

USING_HAMCREST_NS

FIXTURE(IsNotTest)
{
    TEST("integer")
    {
        ASSERT_THAT(0xFF, is_not(0xEE));
        ASSERT_THAT(0xFF, is_not(eq(0xEE)));
    }

    TEST("string")
    {
        ASSERT_THAT("hello", is_not("world"));
        ASSERT_THAT("hello", is_not(eq("world")));

        ASSERT_THAT("hello", is_not(std::string("world")));
        ASSERT_THAT(std::string("hello"), is_not(std::string("world")));
    }
};
