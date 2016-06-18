#ifndef H1D3F7D09_9BDA_4551_A0F8_91D782E64FD4
#define H1D3F7D09_9BDA_4551_A0F8_91D782E64FD4

#include <cum/ext/collection/matcher/IsIn.h>
#include <list>

CUM_NS_BEGIN

template <typename C>
auto in(const C& c) -> IsIn<C, typename C::value_type>*
{
    return new IsIn<C, typename C::value_type>(c);
}

template <typename T>
auto in(const std::initializer_list<T> values) -> IsIn<std::list<T>, T>*
{
    return new IsIn<std::list<T>, T>(values);
}

template <typename T, size_t N>
auto in(T (&arr)[N]) -> IsIn<std::list<T>, T>*
{
    return new IsIn<std::list<T>, T>(std::begin(arr), std::end(arr));
}

CUM_NS_END

#define one_of(...) CUM_NS::in(__VA_ARGS__)

#endif
