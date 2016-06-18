#include "magellan/magellan.hpp"
#include <ccinfra/algo/search.h>
#include <ccinfra/ctnr/array/ArraySize.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    int a[] = {1, 3, 5, 7};
}

FIXTURE(BinarySearchTest)
{
	TEST("should find correct when key is in the middle position")
	{
		int *r = binary_search(begin_a(a), end_a(a), 5);
		ASSERT_THAT(*r, eq(5));
		ASSERT_THAT(position(a, r), eq(2));
	}

	TEST("should return the end when key not find")
	{
		ASSERT_THAT(binary_search(begin_a(a), end_a(a), 6), eq(end_a(a)));
	}
};
