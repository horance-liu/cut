#ifndef H32BCC72A_53DC_44C0_ACF6_F5C048B6D61A
#define H32BCC72A_53DC_44C0_ACF6_F5C048B6D61A

#include <magellan/base/magellan.h>
#include <infra/base/Role.h>

MAGELLAN_NS_BEGIN

DEFINE_ROLE(Protectable)
{
    ABSTRACT(void protect() const);
};

MAGELLAN_NS_END

#endif
