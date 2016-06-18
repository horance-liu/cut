#ifndef H671141B2_B247_440B_8E83_476558110FFF
#define H671141B2_B247_440B_8E83_476558110FFF

#include <ccinfra/ccinfra.h>
#include <ccinfra/base/Uncloneable.h>

CCINFRA_NS_BEGIN

template<typename T>
struct Singleton
{
    static T& getInstance()
    {
        static T instance;
        return instance;
    }

    DISALLOW_COPY_AND_ASSIGN(Singleton)

protected:
    Singleton() {}
};

#define DEF_SINGLETON(object) struct object : ::CCINFRA_NS::Singleton<object>

CCINFRA_NS_END

#endif

