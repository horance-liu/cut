#ifndef _EZ1OGIL29GSDE6HPCZ1L7A1A3TJKJF4TPJMJTWJ6GYEZ66PULN8FV30Z               
#define _EZ1OGIL29GSDE6HPCZ1L7A1A3TJKJF4TPJMJTWJ6GYEZ66PULN8FV30Z

#include <utility>

template <typename Container, typename Unary>
void each(Container&& c, Unary f)
{
    for (auto e : std::forward<Container>(c))
        f(e);
}

#endif
