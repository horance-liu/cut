#include <magellan/hamcrest/ext/collection/helper/IsInHelper.h>
#include <magellan/hamcrest/core/helper/IsHelper.h>
#include <magellan/hamcrest/core/helper/IsNotHelper.h>
#include <assertion/Asserter.h>

USING_HAMCREST_NS

TEST(in, support_all_stl_container_types)
{
    ASSERT_THAT(5, in(std::vector<int>{1, 3, 5}));
    ASSERT_THAT(5, in(std::list<int>{1, 3, 5}));
}

TEST(in, is_as_decorator)
{
    ASSERT_THAT(5, is(in(std::vector<int>{1, 3, 5})));

    ASSERT_THAT(5, is(in({1, 2, 5})));
    ASSERT_THAT(7, is_not(in({1, 2, 5})));
}

TEST(in, support_array)
{
    int arr[]{1, 3, 5};
    ASSERT_THAT(5, in(arr));
}

TEST(in, support_initializer_list)
{
    ASSERT_THAT(5, in({1, 2, 5}));
}

TEST(one_of, is_same_as_in)
{
    ASSERT_THAT(5, one_of(std::vector<int>{1, 3, 5}));
    ASSERT_THAT(5, one_of({1, 3, 5}));

    int arr[]{1, 3, 5};
    ASSERT_THAT(5, one_of(arr));
}
