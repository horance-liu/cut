#ifndef H77D5AE53_F815_4987_87CC_9254557EC4BD
#define H77D5AE53_F815_4987_87CC_9254557EC4BD

#include <algorithm>
#include <iterator>
#include <cui/cui.h>

CUI_NS_BEGIN

#define CUI_RANG(c) std::begin(std::forward<Container>(c)), std::end(std::forward<Container>(c))

template <typename Container, class P>
inline bool all_of(Container&& c, P pred)
{
    return std::all_of(CUI_RANG(c), pred);
}

template <typename Container, class P>
inline bool any_of(Container&& c, P pred)
{
    return std::any_of(CUI_RANG(c), pred);
}


template <typename Container, class P>
inline auto find_if(Container&& c, P pred)
    -> decltype(std::begin(std::forward<Container>(c)))
{
    return std::find_if(CUI_RANG(c), pred);
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
    return std::for_each(CUI_RANG(c), f);
}

template <typename Container, typename OutputIterator, typename Unary>
inline OutputIterator map(Container&& c, OutputIterator result, Unary f)
{
    return std::transform(CUI_RANG(c), result, f);
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
    return details::do_filter(CUI_RANG(c), result, pred);
}

CUI_NS_END

#endif
