#include "magellan/magellan.hpp"
#include <ccinfra/algo/bound.h>
#include <ccinfra/ctnr/array/ArraySize.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    int a[] = {1, 3, 5, 7};
}

FIXTURE(UpperBoundTest)
{
	TEST("should find the upper bound in middle position correct")
	{
	    ASSERT_THAT(upper_bound(a, ARR_SIZE(a), 4), eq(2));
	}

	TEST("should find the upper bound in left edge position correct")
	{
	    ASSERT_THAT(upper_bound(a, ARR_SIZE(a), 0), eq(0));
	}

	TEST("should find the upper bound in last position correct")
	{
	    ASSERT_THAT(upper_bound(a, ARR_SIZE(a), 7), eq(3));
	}

	TEST("should find the upper bound out of right position correct")
	{
	    ASSERT_THAT(upper_bound(a, ARR_SIZE(a), 8), eq(3));
	}
};

FIXTURE(LowerBoundTest)
{
	TEST("should find the upper bound in middle position correct")
	{
	    ASSERT_THAT(lower_bound(a, ARR_SIZE(a), 4), eq(1));
	}

	TEST("should find the upper bound in right edge position correct")
	{
	    ASSERT_THAT(lower_bound(a, ARR_SIZE(a), 8), eq(3));
	}

	TEST("should find the upper bound in left edge position correct")
	{
	    ASSERT_THAT(lower_bound(a, ARR_SIZE(a), 1), eq(0));
	}

	TEST("should find the upper bound out of left edge position correct")
	{
	    ASSERT_THAT(lower_bound(a, ARR_SIZE(a), 0), eq(0));
	}
};


