#ifndef H1D3F7D09_9BDA_4551_A0F8_91D782E64FD4
#define H1D3F7D09_9BDA_4551_A0F8_91D782E64FD4

#include <magellan/hamcrest/ext/collection/matcher/IsIn.h>
#include <list>

template <typename C>
auto in(const C& c) -> HAMCREST_NS::IsIn<C, typename C::value_type>
{
    return HAMCREST_NS::IsIn<C, typename C::value_type>(c);
}

template <typename T>
auto in(const std::initializer_list<T> values) -> HAMCREST_NS::IsIn<std::list<T>, T>
{
    return HAMCREST_NS::IsIn<std::list<T>, T>(values);
}

template <typename T, size_t N>
auto in(T (&arr)[N]) -> HAMCREST_NS::IsIn<std::list<T>, T>
{
    return HAMCREST_NS::IsIn<std::list<T>, T>(std::begin(arr), std::end(arr));
}

#define one_of(...) in(__VA_ARGS__)

#endif
