#include <cut/cut.hpp>
#include <quantity/length/Length.h>

USING_CUM_NS

FIXTURE(LengthTest)
{
    TEST("1 feet should equal to 12 inch")
    {
        ASSERT_THAT(Length(1, FEET), eq(Length(12, INCH)));
    }

    TEST("1 yard should equal to 3 feets")
    {
        ASSERT_THAT(Length(1, YARD), eq(Length(3, FEET)));
    }

    TEST("1 mile should equal to 1760 yards")
    {
        ASSERT_THAT(Length(1, MILE), eq(Length(1760, YARD)));
    }
};

