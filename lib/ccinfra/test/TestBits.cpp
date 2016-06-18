#include "magellan/magellan.hpp"
#include "ccinfra/algo/bits.h"

USING_HAMCREST_NS
USING_CCINFRA_NS

FIXTURE(BitsTest)
{
	TEST("should calc the correct bit mask by macro")
	{
	    ASSERT_THAT(BIT_MASK(0), eq(0));
	    ASSERT_THAT(BIT_MASK(1), eq(1));
	    ASSERT_THAT(BIT_MASK(2), eq(0x3));
	    ASSERT_THAT(BIT_MASK(7), eq(0x7F));
	    ASSERT_THAT(BIT_MASK(8), eq(0xFF));
	    ASSERT_THAT(BIT_MASK(15), eq(0x7FFF));
	    ASSERT_THAT(BIT_MASK(16), eq(0xFFFF));
	    ASSERT_THAT(BIT_MASK(31), eq(0x7FFFFFFF));
	    ASSERT_THAT(BIT_MASK(32), eq(0xFFFFFFFF));
	    ASSERT_THAT(BIT_MASK(63), eq(0x7FFFFFFFFFFFFFFF));
	}

	TEST("should calc the correct bit mask by template function")
	{
	    ASSERT_THAT(bit_mask<U8>(0), eq(0));
	    ASSERT_THAT(bit_mask<U8>(1), eq(1));
	    ASSERT_THAT(bit_mask<U8>(2), eq(0x3));
	    ASSERT_THAT(bit_mask<U8>(7), eq(0x7F));
	    ASSERT_THAT(bit_mask<U8>(8), eq(0xFF));
	    ASSERT_THAT(bit_mask<U16>(15), eq(0x7FFF));
	    ASSERT_THAT(bit_mask<U16>(16), eq(0xFFFF));
	    ASSERT_THAT(bit_mask<U32>(31), eq(0x7FFFFFFF));
	    ASSERT_THAT(bit_mask<U64>(32), eq(0xFFFFFFFF));
	    ASSERT_THAT(bit_mask<U64>(63), eq(0x7FFFFFFFFFFFFFFF));
	}

	TEST("should get the bits value by macro")
	{
	    ASSERT_THAT(GET_BITS_VALUE(0xaa, 2, 2), eq(0x2));
	    ASSERT_THAT(GET_BITS_VALUE(0xaa, 3, 2), eq(0x1));
	    ASSERT_THAT(GET_BITS_VALUE(0xaa, 3, 3), eq(0x5));
	    ASSERT_THAT(GET_BITS_VALUE(0xaa, 7, 4), eq(0x1));
	    ASSERT_THAT(GET_BITS_VALUE(0xccaaaaaaaaaaaaaa, 60, 4), eq(0xc));
	}

	TEST("should get the bits value by template function")
	{
	    ASSERT_THAT(bit_value(0xaa, 2, 2), eq(0x2));
	    ASSERT_THAT(bit_value(0xaa, 3, 2), eq(0x1));
	    ASSERT_THAT(bit_value(0xaa, 3, 3), eq(0x5));
	    ASSERT_THAT(bit_value(0xaa, 7, 4), eq(0x1));

	    ASSERT_THAT(bit_value(0xccaaaaaaaaaaaaaa, 60, 4), eq(0xc));
	}

	TEST("should get the given bit value by macro")
	{
		ASSERT_THAT(IS_BIT_ON(0xaa, 2), be_false());
		ASSERT_THAT(IS_BIT_ON(0xccaaaaaaaaaaaaaa, 63), be_true());
	}

	TEST("should get the given bit value by template function")
	{
		ASSERT_THAT(is_bit_on(0xaa, 2), be_false());
	    ASSERT_THAT(is_bit_on(0xccaaaaaaaaaaaaaa, 63), be_true());
	}
};


