#include <cum/ext/number/def/IsNaNDef.h>
#include <cum/core/def/IsDef.h>
#include <cum/core/def/IsNotDef.h>
#include <cut/cut.hpp>
#include <math.h>

USING_CUM_NS

FIXTURE(IsNanTest)
{
    TEST("double")
    {
        ASSERT_THAT(sqrt(-1.0), nan());
        ASSERT_THAT(sqrt(-1.0), is(nan()));

        ASSERT_THAT(1.0/0.0,  is_not(nan()));
        ASSERT_THAT(-1.0/0.0, is_not(nan()));
    }
};
