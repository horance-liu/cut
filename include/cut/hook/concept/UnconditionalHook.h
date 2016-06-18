#ifndef H9ABDDEDF_C97D_4D65_80C2_33DE40D6F46A
#define H9ABDDEDF_C97D_4D65_80C2_33DE40D6F46A

#include <cut/cut.h>
#include <cub/dci/Role.h>

CUT_NS_BEGIN

DEFINE_ROLE(UnconditionalHook)
{
    ABSTRACT(void invoke());
};

CUT_NS_END

#endif
