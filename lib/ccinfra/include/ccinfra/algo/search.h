#ifndef H1BEBC79D_5BA8_2341_AD8C_94F820EC7D5B
#define H1BEBC79D_5BA8_2341_AD8C_94F820EC7D5B

#include <ccinfra/ccinfra.h>
#include <algorithm>

CCINFRA_NS_BEGIN

template <typename ForwardIterator, typename T>
ForwardIterator binary_search(ForwardIterator first, ForwardIterator last, const T& val)
{
    ForwardIterator iter = std::lower_bound(first, last, val);
    if (iter != last && *iter == val) return iter;
    else return last;
}

CCINFRA_NS_END

#endif

