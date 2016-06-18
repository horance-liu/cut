#include "magellan/magellan.hpp"
#include <ccinfra/mem/LinkedAllocator.h>
#include <ccinfra/ctnr/array/ArraySize.h>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
    int array[] = {0, 1, 2, 3, 4};
}

FIXTURE(LinkedAllocatorTest)
{
    LinkedAllocatorTest()
    : allocator(array, MAX_ALLOC_NUM)
    {
    }

    TEST("should has free slot num when init")
    {
    	ASSERT_THAT(allocator.isBusyListEmpty(), be_true());
    	ASSERT_THAT(allocator.isFreeListEmpty(), be_false());
    }

    TEST("should alloc ok when has free slots")
    {
        for(int i = 0; i < MAX_ALLOC_NUM; i++)
        {
            const int* x = allocator.alloc();
            ASSERT_THAT(__NOT_NULL(x), be_true());
            ASSERT_THAT(*x, eq(i));
        }

        const int* x = allocator.alloc();
        ASSERT_THAT(__IS_NULL(x), be_true());
    }

    TEST("should alloc ok when free slots")
    {
        for(int i = 0; i < MAX_ALLOC_NUM - 1; i++)
        {
            allocator.alloc();
        }

        const int* x = allocator.alloc();
        ASSERT_THAT(__NOT_NULL(x), be_true());

        const int *y = allocator.alloc();
        ASSERT_THAT(__IS_NULL(y), be_true());

        ASSERT_THAT(allocator.dealloc(*x), eq(CCINFRA_SUCCESS));

        y = allocator.alloc();
        ASSERT_THAT(__NOT_NULL(y), be_true());
        ASSERT_THAT(*y, eq(2));
    }

    const static int MAX_ALLOC_NUM = 3;
    LinkedAllocator<int, ARR_SIZE(array)> allocator;
};


