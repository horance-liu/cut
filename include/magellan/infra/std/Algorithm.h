#ifndef HA980B189_62DA_454B_B213_0905ED542E61
#define HA980B189_62DA_454B_B213_0905ED542E61

#include <magellan/infra/std/stdext.h>
#include <utility>
#include <algorithm>
#include <numeric>
#include <sstream>

STDEXT_NS_BEGIN

#define RANG(c) std::begin(std::forward<Container>(c)), std::end(std::forward<Container>(c))

template <typename Container, class P>
inline auto find_if(Container&& c, P pred)
    -> decltype(std::begin(std::forward<Container>(c)))
{
    return std::find_if(RANG(c), pred);
}

template <typename Container, class T>
inline auto find(Container&& c, const T& t)
    -> decltype(std::begin(std::forward<Container>(c)))
{
    return find_if(std::forward<Container>(c), [&t] (const T& e) { return e == t; });
}

template <typename Container, typename Unary>
inline Unary each(Container&& c, Unary f)
{
    return std::for_each(RANG(c), f);
}

template <typename Container, typename OutputIterator, typename Unary>
inline OutputIterator map(Container&& c, OutputIterator result, Unary f)
{
    return std::transform(RANG(c), result, f);
}

template <class Container, class T, class Binary>
inline T reduce(Container&& container, T init, Binary f)
{
    for (auto e : container)
        f(init, e);

    return init;
}

namespace details
{
    template <class InputIterator, class OutputIterator, class Predicate>
    inline OutputIterator
    do_filter(InputIterator first, InputIterator last, OutputIterator result, Predicate pred)
    {
        for (; first != last; ++first, ++result)
            if (pred(*first))
                *result = *first;
        return result;
    }
}

template <typename Container, typename OutputIterator, typename Predicate>
inline OutputIterator filter(Container&& c, OutputIterator result, Predicate pred)
{
    return details::do_filter(RANG(c), result, pred);
}

template <typename Container>
void clear(Container&& c)
{
    each(c, [](auto e) { delete e; });
    c.clear();
}

namespace details
{
    template <typename Iterator>
    std::string do_join(Iterator first, Iterator last, const std::string& separator)
    {
        std::ostringstream ss;

        if (first != last)
            ss << *first++;

        while (first != last)
            ss << separator << *first++;

        return ss.str();
    }
}


template <typename Container>
std::string join(Container&& c, const std::string& separator)
{
    return details::do_join(RANG(c), separator);
}

STDEXT_NS_END

#endif
