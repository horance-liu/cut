#include <cut/cut.hpp>
#include <hamcrest/core/def/IsDef.h>
#include <hamcrest/core/def/BoolDef.h>

USING_HAMCREST_NS

FIXTURE(IsTest)
{
    TEST("integer")
    {
        ASSERT_THAT(0xff, is(0xFF));
        ASSERT_THAT(0xff, is(eq(0xFF)));
    }

    TEST("bool")
    {
        ASSERT_THAT(true,  is(true));
        ASSERT_THAT(false, is(false));

        ASSERT_THAT(true,  is(eq(true)));
        ASSERT_THAT(false, is(eq(false)));
    }

    TEST("be_true/be_false as syntactic sugar")
    {
        ASSERT_THAT(true,  be_true());
        ASSERT_THAT(false, be_false());
    }

    TEST("string")
    {
        ASSERT_THAT("hello", is("hello"));
        ASSERT_THAT("hello", is(eq("hello")));

        ASSERT_THAT("hello", is(std::string("hello")));
        ASSERT_THAT(std::string("hello"), is(std::string("hello")));
    }
};
