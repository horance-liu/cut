#include "magellan/magellan.hpp"
#include <ccinfra/mem/Maybe.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

FIXTURE(MaybeTest)
{
	TEST("should be unpresent when init")
	{
	    Maybe<int> x;

	    ASSERT_THAT(x.isPresent(), be_false());
	}

	TEST("should be present when update")
	{
	    Maybe<int> x;

	    x.update(5);

	    ASSERT_THAT(x.isPresent(), be_true());
	    ASSERT_THAT(*x, eq(5));
	}

	TEST("should be present when force effective")
	{
	    Maybe<int> x;

	    x.forceEffective();

	    ASSERT_THAT(x.isPresent(), be_true());
	    ASSERT_THAT(*x, eq(0));
	}

	TEST("should compare unequal when not effective")
	{
	    Maybe<int> x;
	    Maybe<int> y(2);

	    ASSERT_THAT(x == y, be_false());
	}

	TEST("should compare equal when effective")
	{
	    Maybe<int> x;
	    Maybe<int> y(2);

	    x.update(2);

	    ASSERT_THAT(x == y, be_true());
	}
};


