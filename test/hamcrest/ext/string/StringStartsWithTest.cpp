#include <magellan/hamcrest/core/helper/IsHelper.h>
#include <magellan/hamcrest/ext/string/helper/StringStartsWithHelper.h>
#include <assertion/Asserter.h>

TEST(starts_with, case_sensitive)
{
    ASSERT_THAT("ruby-cpp", starts_with("ruby"));
    ASSERT_THAT("ruby-cpp", is(starts_with("ruby")));

    ASSERT_THAT(std::string("ruby-cpp"), starts_with("ruby"));
    ASSERT_THAT("ruby-cpp", starts_with(std::string("ruby")));
    ASSERT_THAT(std::string("ruby-cpp"), starts_with(std::string("ruby")));
}

TEST(starts_with, ignoring_case)
{
    ASSERT_THAT("ruby-cpp", starts_with_ignoring_case("Ruby"));
    ASSERT_THAT("ruby-cpp", is(starts_with_ignoring_case("Ruby")));

    ASSERT_THAT(std::string("ruby-cpp"), starts_with_ignoring_case("RUBY"));
    ASSERT_THAT("Ruby-Cpp", starts_with_ignoring_case(std::string("rUBY")));
    ASSERT_THAT(std::string("RUBY-CPP"), starts_with_ignoring_case(std::string("ruby")));
}
