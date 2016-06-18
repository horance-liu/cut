#include <hamcrest/core/def/IsDef.h>
#include <hamcrest/ext/string/def/StringEndsWithDef.h>
#include <cut/cut.hpp>

USING_HAMCREST_NS

FIXTURE(EndsWithTest)
{
    TEST("case sensitive")
    {
        ASSERT_THAT("ruby-cpp", ends_with("cpp"));
        ASSERT_THAT("ruby-cpp", is(ends_with("cpp")));

        ASSERT_THAT(std::string("ruby-cpp"), ends_with("cpp"));
        ASSERT_THAT("ruby-cpp", ends_with(std::string("cpp")));
        ASSERT_THAT(std::string("ruby-cpp"), ends_with(std::string("cpp")));
    }

    TEST("ignoring case")
    {
        ASSERT_THAT("ruby-cpp", ends_with_ignoring_case("Cpp"));
        ASSERT_THAT("ruby-cpp", is(ends_with_ignoring_case("CPP")));

        ASSERT_THAT(std::string("ruby-cpp"), ends_with_ignoring_case("Cpp"));
        ASSERT_THAT("Ruby-Cpp", ends_with_ignoring_case(std::string("cPP")));
        ASSERT_THAT(std::string("RUBY-CPP"), ends_with_ignoring_case(std::string("cpp")));
    }
};

