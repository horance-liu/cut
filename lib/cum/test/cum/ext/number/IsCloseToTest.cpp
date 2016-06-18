#include <cum/ext/number/def/IsCloseToDef.h>
#include <cut/cut.hpp>

USING_CUM_NS

FIXTURE(CloseToTest)
{
    TEST("double")
    {
        ASSERT_THAT(1.0, close_to(1.0, 0.5));
        ASSERT_THAT(0.5, close_to(1.0, 0.5));
        ASSERT_THAT(1.5, close_to(1.0, 0.5));
    }

    TEST("float")
    {
        ASSERT_THAT(1.0f, close_to(1.0, 0.5f));
        ASSERT_THAT(0.5f, close_to(1.0f, 0.5));
        ASSERT_THAT(1.5f, close_to(1.0f, 0.5f));
    }

    TEST("long double")
    {
        ASSERT_THAT(1.0L, close_to(1.0, 0.5));
        ASSERT_THAT(0.5L, close_to(1.0, 0.5L));
        ASSERT_THAT(1.5L, close_to(1.0L, 0.5L));
    }
};
