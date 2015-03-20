#ifndef KLSAFJLKAEFI_NXCN_SDFKWEJLK_FSDYUIWERIUYXC_NMCXHS
#define KLSAFJLKAEFI_NXCN_SDFKWEJLK_FSDYUIWERIUYXC_NMCXHS

#include <magellan/infra/std/stdext.h>

STDEXT_NS_BEGIN

template<typename T>
struct Singleton
{
    static T& getInstance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() {}
};

#define DEF_SINGLETON(object) struct object : stdext::Singleton<object>

STDEXT_NS_END

#endif
