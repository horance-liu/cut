#ifndef HF6201AF3_C3A9_47FC_A3A6_1C91D7F33FEC
#define HF6201AF3_C3A9_47FC_A3A6_1C91D7F33FEC

#include <ccinfra/base/BaseTypes.h>
#include <ccinfra/mem/Placement.h>

CCINFRA_NS_BEGIN

template<bool hasDefaultConstructor>
struct DefaultConstructor
{
    template <typename T>
    static void construct(Placement<T>elem);

    template <typename T, size_t N>
    static void construct(Placement<T>(&elems)[N]);
};

template<> struct DefaultConstructor<true>
{
    template <typename T>
    static void construct(Placement<T>elem)
    {
        new (elem.alloc()) T();
    }

    template <typename T, size_t N>
    static void construct(Placement<T>(&elems)[N])
    {
        for(size_t i = 0; i < N; i++)
        {
            new (elems[i].alloc()) T();
        }
    }
};

CCINFRA_NS_END

#endif
