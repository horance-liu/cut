#include <magellan/hamcrest/core/helper/AnythingHelper.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

TEST(anything, always_be_matched)
{
    ASSERT_THAT(1, anything(int));
    ASSERT_THAT(1u, anything(unsigned int));
    ASSERT_THAT(1.0, anything(double));
    ASSERT_THAT(1.0f, anything(float));
    ASSERT_THAT(false, anything(bool));
    ASSERT_THAT(true, anything(bool));
    ASSERT_THAT(nullptr, anything(std::nullptr_t));
}

TEST(anything, allow_implicit_type_conversion)
{
    ASSERT_THAT(1u, anything(int));
    ASSERT_THAT(1.0f, anything(float));
    ASSERT_THAT(false, anything(int));
    ASSERT_THAT(nullptr, anything(std::nullptr_t));
}
