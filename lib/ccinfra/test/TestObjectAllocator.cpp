#include "magellan/magellan.hpp"
#include <ccinfra/mem/ObjectAllocator.h>
#include <ccinfra/algo/loop.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    struct Foo
    {
        Foo(int a) : x(a)
        {
        }

        int getValue() const
        {
            return x;
        }

        DECL_OPERATOR_NEW();

    private:
        int x;
    };

    const U16 MAX_SLOT_NUM = 2;
}

DEF_OBJ_ALLOCATOR(Foo, MAX_SLOT_NUM);

FIXTURE(ObjectAllocatorTest)
{
	TEST("should have correct free slot when init")
	{
	    ASSERT_THAT(FooAllocator.getFreeSlotNum(), eq(MAX_SLOT_NUM));
	}

	TEST("should alloc OK when has free slot")
	{
	    Foo* foo = new Foo(3);
	    ASSERT_THAT(__NOT_NULL(foo), be_true());
	    ASSERT_THAT(FooAllocator.getFreeSlotNum(), eq(MAX_SLOT_NUM - 1));

	    delete foo;
	    ASSERT_THAT(FooAllocator.getFreeSlotNum(), eq(MAX_SLOT_NUM));
	}

	TEST("should not alloc when has no free slot")
	{
	    Foo* foos[MAX_SLOT_NUM] = {__null_ptr};

	    FOR_EACH_0(i, MAX_SLOT_NUM)
	    {
	        foos[i] = new Foo(0);
	    }

	    Foo* foo = new Foo(0);
	    ASSERT_THAT(__IS_NULL(foo), be_true());

	    FOR_EACH_0(i, MAX_SLOT_NUM)
	    {
	    	ASSERT_THAT(__NOT_NULL(foos[i]), be_true());
	        delete foos[i];
	    }

	    foo = new Foo(0);
	    ASSERT_THAT(__NOT_NULL(foo), be_true());
	    delete foo;
	}
};


