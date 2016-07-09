#include <cut/cut.hpp>
#include <cum/core/def/AnythingDef.h>

USING_CUM_NS

FIXTURE(AnythingTest)
{
    TEST("should always be matched")
    {
        ASSERT_THAT(1, anything<int>());
        ASSERT_THAT(1u, anything<unsigned int>());
        ASSERT_THAT(1.0, anything<double>());
        ASSERT_THAT(1.0f, anything<float>());
        ASSERT_THAT(false, anything<bool>());
        ASSERT_THAT(true, anything<bool>());
        ASSERT_THAT(nullptr, anything<std::nullptr_t>());
    }

    TEST("should allow implicit type conversion")
    {
        ASSERT_THAT(1u, anything<int>());
        ASSERT_THAT(1.0f, anything<float>());
        ASSERT_THAT(false, anything<int>());
        ASSERT_THAT(nullptr, anything<std::nullptr_t>());
    }

    TEST("should support _ as syntactic sugar")
    {
        ASSERT_THAT(1u, _(int));
        ASSERT_THAT(1.0f, _(float));
        ASSERT_THAT(false, _(int));
        ASSERT_THAT(nullptr, _(std::nullptr_t));
    }
};
