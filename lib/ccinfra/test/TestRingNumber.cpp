#include "magellan/magellan.hpp"
#include <ccinfra/ctnr/number/RingNumber.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

FIXTURE(RingNumberTest)
{
	TEST("should compare equal when ring number init equal")
	{
		RingNumber<U8, 10> r1(1);
		RingNumber<U8, 10> r2(11);

		ASSERT_THAT(r1 == r2, be_true());
	}

	TEST("should compare unequal when ring number init unequal")
	{
		RingNumber<U8, 10> r1(2);
		RingNumber<U8, 10> r2(11);

		ASSERT_THAT(r1 == r2, be_false());
	}

	TEST("should compare equal when ring number add to equal")
	{
		RingNumber<U8, 10> r1(2);
		RingNumber<U8, 10> r2(11);

		ASSERT_THAT(r1 == (++r2), be_true());
	}

	TEST("should compare equal when ring number move to equal")
	{
		RingNumber<U8, 10> r1(4);
		RingNumber<U8, 10> r2(11);

		ASSERT_THAT((r1 << 2) == (r2 >> 11), be_true());
	}
};
