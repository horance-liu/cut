#ifndef H21FC591B_7FC2_409B_81A6_64FBDE5B218C
#define H21FC591B_7FC2_409B_81A6_64FBDE5B218C

/*
 *     Traits for lambda parameters and result type, Using as the example below:
 *
 *     auto f = [](int x, char y){ return double(x + y); };
 *
 *     TypeIndex<0, Lambda<decltype(f)>::Result>::Result y;  // double
 *     TypeIndex<1, Lambda<decltype(f)>::Result>::Result y;  // int
 *     TypeIndex<2, Lambda<decltype(f)>::Result>::Result y;  // char
 *
 */

#include <ccinfra/ccinfra.h>

CCINFRA_NS_BEGIN

template<typename Head, typename... Args>
struct TypePack
{
    template<typename... Args1>
    struct Pack
    {
        typedef TypePack<Args1...> Self;
    };

    typedef Head Result;
    typedef Pack<Args...> Next;
};

template<size_t index, typename Func>
struct TypeIndex
{
    typedef typename TypeIndex<index - 1, typename Func::Next::Self>::Result Result;
};

template<typename Func>
struct TypeIndex<0, Func>
{
    typedef typename Func::Result Result;
};

template <typename Func>
struct Lambda
{
    typedef typename Lambda<decltype(&Func::operator())>::Result Result;
};

template<typename Ret, typename Class, typename... Args>
struct Lambda<Ret (Class::*)(Args...)>
{
    typedef TypePack<Ret, Args...> Result;
};

template<typename Ret, typename Class, typename... Args>
struct Lambda<Ret (Class::*)(Args...) const>
{
    typedef TypePack<Ret, Args...> Result;
};

template<typename Ret, typename... Args>
struct Lambda<Ret (*)(Args...)>
{
    typedef TypePack<Ret, Args...> Result;
};

CCINFRA_NS_END

#endif
