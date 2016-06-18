#ifndef H4358042D_C5CA_48CF_82A6_05A9B0B3B8EA
#define H4358042D_C5CA_48CF_82A6_05A9B0B3B8EA

#include <ccinfra/ccinfra.h>
#include <string.h>

CCINFRA_NS_BEGIN

template<typename KEY>
struct EqualFn
{
    bool operator()(const KEY& x, const KEY& y) const
    {
        return x == y;
    }
};

template<>
struct EqualFn<char*>
{
    bool operator()(const char* x, const char* y) const
    {
        return strcmp(x, y) == 0;
    }
};

template<>
struct EqualFn<const char*>
{
    bool operator()(const char* x, const char* y) const
    {
        return strcmp(x, y) == 0;
    }
};

CCINFRA_NS_END

#endif
