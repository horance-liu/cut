#include <magellan/magellan.hpp>
#include <ccinfra/algo/range.h>
#include <ccinfra/base/StaticAssert.h>
#include <type_traits>

USING_HAMCREST_NS

namespace
{
    int arr[] = {-1, -2, 3, 4};
    std::vector<int> v1 {-1, -2, 3, 4};
    const std::vector<int> v2 {-1, -2, 3, 4};
}

#define STATIC_ASSERT_TYPE(expect_type, expr) \
	STATIC_ASSERT((std::is_same<expect_type, decltype(expr)>::value))

#define STATIC_ASSERT_SAME_TYPE(expect_type, actual_type) \
    STATIC_ASSERT_TRUE((std::is_same<expect_type, actual_type>::value))

#define STATIC_ASSERT_RVALUE_REF(expr) \
    STATIC_ASSERT_TRUE(std::is_rvalue_reference<decltype(expr)>::value)

#define STATIC_ASSERT_LVALUE_REF(expr) \
    STATIC_ASSERT_TRUE(std::is_lvalue_reference<decltype(expr)>::value)

FIXTURE(AlgorithmTest)
{
   TEST("find support non const container")
    {
        auto found = ccinfra::find(v1, 3);

        STATIC_ASSERT_TYPE(std::vector<int>::iterator, found);
        ASSERT_THAT(*found, is(3));
    }

    TEST("find support const container")
    {
        auto found = ccinfra::find(v2, 3);

        STATIC_ASSERT_TYPE(std::vector<int>::const_iterator, found);
        ASSERT_THAT(*found, is(3));
    }

    TEST("find_if support non const container")
    {
        auto found = ccinfra::find_if(v1, [](int e) { return e > 0; });

        STATIC_ASSERT_TYPE(std::vector<int>::iterator, found);
        ASSERT_THAT(*found, is(3));
    }

    TEST("find_if support const container")
    {
        auto found = ccinfra::find_if(v2, [](int e) { return e > 0; });

        STATIC_ASSERT_TYPE(std::vector<int>::const_iterator, found);
        ASSERT_THAT(*found, is(3));
    }

    TEST("map")
    {
        std::vector<int> v;
        ccinfra::map(v1, std::back_inserter(v), [](int e) { return e > 0 ? e : -e; });

        ASSERT_THAT(v[0], is(1));
        ASSERT_THAT(v[1], is(2));
        ASSERT_THAT(v[2], is(3));
        ASSERT_THAT(v[3], is(4));
    }

    TEST("reduce")
    {
        auto sum = ccinfra::reduce(arr, 0, [](int& sum, int e) { sum += e; });

        ASSERT_THAT(sum, is(4));
    }

    TEST("filter")
    {
        std::vector<int> v;
        ccinfra::filter(arr, std::back_inserter(v), [](int e) { return e > 0; });

        ASSERT_THAT(v[0], is(3));
        ASSERT_THAT(v[1], is(4));
    }

    TEST("each")
    {
        auto sum = 0;
        ccinfra::each(arr, [&sum](int e) { sum += e; });

        ASSERT_THAT(sum, is(4));
    }
};
