#include <magellan/magellan.hpp>
#include <hamcrest/core/def/ComparatorDef.h>
#include <hamcrest/core/def/IsDef.h>
#include <hamcrest/core/def/IsNotDef.h>

USING_HAMCREST_NS

FIXTURE(EqualToTest)
{
    TEST("should allow compare to integer")
    {
        ASSERT_THAT(0xFF, eq(0xFF));
        ASSERT_THAT(0xFF, is(eq(0xFF)));

        ASSERT_THAT(0xFF, is(0xFF));
        ASSERT_THAT(0xFF == 0xFF, is(true));
    }

    TEST("should allow compare to bool")
    {
        ASSERT_THAT(true, eq(true));
        ASSERT_THAT(false, eq(false));
    }

    TEST("should allow compare to string")
    {
        ASSERT_THAT("hello", eq("hello"));
        ASSERT_THAT("hello", eq(std::string("hello")));
        ASSERT_THAT(std::string("hello"), eq(std::string("hello")));
    }
};

FIXTURE(NotEqualToTest)
{
    TEST("should allow compare to integer")
    {
        ASSERT_THAT(0xFF, ne(0xEE));

        ASSERT_THAT(0xFF, is_not(0xEE));
        ASSERT_THAT(0xFF, is_not(eq(0xEE)));
        ASSERT_THAT(0xFF != 0xEE, is(true));
    }

    TEST("should allow compare to boolean")
    {
        ASSERT_THAT(true, ne(false));
        ASSERT_THAT(false, ne(true));
    }

    TEST("should allow compare to string")
    {
        ASSERT_THAT("hello", ne("world"));
        ASSERT_THAT("hello", ne(std::string("world")));
        ASSERT_THAT(std::string("hello"), ne(std::string("world")));
    }
};

FIXTURE(LessToTest)
{
    TEST("should allow compare to integer")
    {
        ASSERT_THAT(0xEE, lt(0xFF));
        ASSERT_THAT(0xEE, is(lt(0xFF)));

        ASSERT_THAT(0xEE < 0xFF, is(true));
    }

    TEST("should allow compare to string")
    {
        ASSERT_THAT("hello", lt("world"));
        ASSERT_THAT("hello", lt(std::string("world")));
        ASSERT_THAT(std::string("hello"), lt(std::string("world")));
    }
};

FIXTURE(LessOrEqualToTest)
{
    TEST("should allow compare to integer")
    {
        ASSERT_THAT(0xEE, le(0xFF));
        ASSERT_THAT(0xEE, le(0xEE));
    }

    TEST("should allow compare to string")
    {
        ASSERT_THAT("hello", le("hello"));
        ASSERT_THAT("hello", le(std::string("hello")));
        ASSERT_THAT(std::string("hello"), le(std::string("hello")));

        ASSERT_THAT("hello", le("world"));
        ASSERT_THAT("hello", le(std::string("world")));
        ASSERT_THAT(std::string("hello"), le(std::string("world")));
    }
};

FIXTURE(GreaterToTest)
{
    TEST("should allow compare to integer")
    {
        ASSERT_THAT(0xFF, gt(0xEE));
        ASSERT_THAT(0xFF, is(gt(0xEE)));
    }

    TEST("should allow compare to string")
    {
        ASSERT_THAT("world", gt("hello"));
        ASSERT_THAT("world", gt(std::string("hello")));
        ASSERT_THAT(std::string("world"), gt(std::string("hello")));
    }
};

FIXTURE(GreaterOrEqualToTest)
{
    TEST("should allow compare to integer")
    {
        ASSERT_THAT(0xFF, ge(0xEE));
        ASSERT_THAT(0xFF, ge(0xFF));
    }

    TEST("should allow compare to string")
    {
        ASSERT_THAT("world", ge("hello"));
        ASSERT_THAT("world", ge(std::string("hello")));
        ASSERT_THAT(std::string("world"), ge(std::string("hello")));

        ASSERT_THAT("world", ge("world"));
        ASSERT_THAT("world", ge(std::string("world")));
        ASSERT_THAT(std::string("world"), ge(std::string("world")));
    }
};
