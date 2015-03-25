#include <magellan/magellan.hpp>
#include "quantity/length/Length.h"

USING_HAMCREST_NS

FIXTURE(LegnthTest)
{
    TEST("1 feet should equal to 12 inch")
    {
        ASSERT_THAT(Length(1, FEET), equal_to(Length(12, INCH)));
    }

    TEST("1 yard should equal to 3 feets")
    {
        ASSERT_THAT(Length(1, YARD), equal_to(Length(3, FEET)));
    }

    TEST("1 mile should equal to 1760 yards")
    {
        ASSERT_THAT(Length(1, MILE), equal_to(Length(1760, YARD)));
    }
};

