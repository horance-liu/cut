#include <hamcrest/core/helper/IsHelper.h>
#include <hamcrest/ext/string/helper/StringEndsWithHelper.h>
#include <assertion/Asserter.h>

TEST(ends_with, case_sensitive)
{
    ASSERT_THAT("ruby-cpp", ends_with("cpp"));
    ASSERT_THAT("ruby-cpp", is(ends_with("cpp")));

    ASSERT_THAT(std::string("ruby-cpp"), ends_with("cpp"));
    ASSERT_THAT("ruby-cpp", ends_with(std::string("cpp")));
    ASSERT_THAT(std::string("ruby-cpp"), ends_with(std::string("cpp")));
}

TEST(ends_with, ignoring_case)
{
    ASSERT_THAT("ruby-cpp", ends_with_ignoring_case("Cpp"));
    ASSERT_THAT("ruby-cpp", is(ends_with_ignoring_case("CPP")));

    ASSERT_THAT(std::string("ruby-cpp"), ends_with_ignoring_case("Cpp"));
    ASSERT_THAT("Ruby-Cpp", ends_with_ignoring_case(std::string("cPP")));
    ASSERT_THAT(std::string("RUBY-CPP"), ends_with_ignoring_case(std::string("cpp")));
}
