#include <hamcrest/core/def/IsDef.h>
#include <hamcrest/ext/string/def/StringContainsDef.h>
#include <magellan/magellan.hpp>

USING_HAMCREST_NS

FIXTURE(ContainsSubStringTest)
{
    TEST("case sensitive")
    {
        ASSERT_THAT("ruby-cpp", contains_string("cpp"));
        ASSERT_THAT("ruby-cpp", is(contains_string("cpp")));

        ASSERT_THAT(std::string("ruby-cpp"), contains_string("cpp"));
        ASSERT_THAT("ruby-cpp", contains_string(std::string("cpp")));
        ASSERT_THAT(std::string("ruby-cpp"), contains_string(std::string("cpp")));
    }

    TEST("ignoring case")
    {
        ASSERT_THAT("ruby-cpp", contains_string_ignoring_case("Cpp"));
        ASSERT_THAT("ruby-cpp", is(contains_string_ignoring_case("CPP")));

        ASSERT_THAT(std::string("ruby-cpp"), contains_string_ignoring_case("Cpp"));
        ASSERT_THAT("Ruby-Cpp", contains_string_ignoring_case(std::string("cPP")));
        ASSERT_THAT(std::string("RUBY-CPP"), contains_string_ignoring_case(std::string("cpp")));
    }
};
