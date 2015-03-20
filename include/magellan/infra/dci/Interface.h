#ifndef __DCM_BASE_INTERFACE_DEF_H__
#define __DCM_BASE_INTERFACE_DEF_H__

#include <magellan/infra/dci/Keywords.h>

typedef unsigned int InterfaceId;

namespace dci {

namespace details
{
    struct Dummy {};

    template <typename T_B1, typename T_B2, typename T_B3>
    struct BaseTraits
    {
        struct Base : T_B1, T_B2, T_B3 
        {
            virtual ~Base() {}
        };
    };

    template <typename T_B1, typename T_B2>
    struct BaseTraits<T_B1, T_B2, Dummy>
    {
        struct Base : T_B1, T_B2 
        {
            virtual ~Base() {}
        };
    };

    template <typename T_B1>
    struct BaseTraits<T_B1, Dummy, Dummy>
    {
        typedef T_B1 Base;
    };

    template <>
    struct BaseTraits<Dummy, Dummy, Dummy>
    {
        struct Base
        {
            virtual ~Base() {}
        };
    };

    template < InterfaceId I_IID
             , typename T_B1 = Dummy
             , typename T_B2 = Dummy
             , typename T_B3 = Dummy>
    struct Interface : BaseTraits<T_B1, T_B2, T_B3>::Base
    {
        enum { E_IID = I_IID };
        virtual ~Interface() {}
    };
}

}

#define DEF_INTERFACE(iface, iid, ...) \
struct iface : dci::details::Interface<iid, ##__VA_ARGS__>

#define IS_INTERFACE(iid, ...) , dci::details::Interface<iid, ##__VA_ARGS__>

#endif
