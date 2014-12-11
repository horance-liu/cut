#include <hamcrest/core/helper/IsHelper.h>
#include <hamcrest/core/helper/StringContainsHelper.h>
#include <assertion/Asserter.h>

TEST(constains_string, case_sensitive)
{
    ASSERT_THAT("ruby-cpp", contains_string("cpp"));
    ASSERT_THAT("ruby-cpp", is(contains_string("cpp")));

    ASSERT_THAT(std::string("ruby-cpp"), contains_string("cpp"));
    ASSERT_THAT("ruby-cpp", contains_string(std::string("cpp")));
    ASSERT_THAT(std::string("ruby-cpp"), contains_string(std::string("cpp")));
}

TEST(contains_string, ignoring_case)
{
    ASSERT_THAT("ruby-cpp", contains_string_ignoring_case("Cpp"));
    ASSERT_THAT("ruby-cpp", is(contains_string_ignoring_case("CPP")));

    ASSERT_THAT(std::string("ruby-cpp"), contains_string_ignoring_case("Cpp"));
    ASSERT_THAT("Ruby-Cpp", contains_string_ignoring_case(std::string("cPP")));
    ASSERT_THAT(std::string("RUBY-CPP"), contains_string_ignoring_case(std::string("cpp")));
}
