#include <hamcrest/ext/collection/def/IsInDef.h>
#include <hamcrest/core/def/IsDef.h>
#include <hamcrest/core/def/IsNotDef.h>
#include <magellan/magellan.hpp>

USING_HAMCREST_NS

FIXTURE(InTest)
{
    TEST("support all stl container types")
    {
        ASSERT_THAT(5, in(std::vector<int>{1, 3, 5}));
        ASSERT_THAT(5, in(std::list<int>{1, 3, 5}));
    }

    TEST("is can be as decorator")
    {
        ASSERT_THAT(5, is(in(std::vector<int>{1, 3, 5})));

        ASSERT_THAT(5, is(in({1, 2, 5})));
        ASSERT_THAT(7, is_not(in({1, 2, 5})));
    }

    TEST("support c style array")
    {
        int arr[]{1, 3, 5};
        ASSERT_THAT(5, in(arr));
    }

    TEST("support initializer_list")
    {
        ASSERT_THAT(5, in({1, 2, 5}));
    }

    TEST("one_of is same_as with in")
    {
        ASSERT_THAT(5, one_of(std::vector<int>{1, 3, 5}));
        ASSERT_THAT(5, one_of({1, 3, 5}));

        int arr[]{1, 3, 5};
        ASSERT_THAT(5, one_of(arr));
    }
};
