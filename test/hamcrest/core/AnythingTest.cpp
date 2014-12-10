#include <gtest/gtest.h>
#include <hamcrest/core/Anything.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

TEST(anything, always_be_matched)
{
    ASSERT_THAT(1, anything<int>());
    ASSERT_THAT(false, anything<bool>());
    ASSERT_THAT(true, anything<bool>());
    ASSERT_THAT(nullptr, anything<std::nullptr_t>());
}
