#ifndef H9ABDDEDF_C97D_4D65_80C2_33DE40D6F46A
#define H9ABDDEDF_C97D_4D65_80C2_33DE40D6F46A

#include <magellan/magellan.h>
#include <l0-infra/dci/Role.h>

MAGELLAN_NS_BEGIN

DEFINE_ROLE(UnconditionalHook)
{
    ABSTRACT(void invoke());
};

MAGELLAN_NS_END

#endif
