#ifndef _R2RGF94XEYGH3CTU7C57VEO4HSA4DG6RFRG0FRS2TOKTBMIYZM8SCDWP               
#define _R2RGF94XEYGH3CTU7C57VEO4HSA4DG6RFRG0FRS2TOKTBMIYZM8SCDWP

#include <cui/dci/__Role__.h>
#include <cut/cut.h>

CUT_NS_BEGIN

struct Test;

__TRAIT__(TestFunctor)
{
    __HAS_ROLE__(Test);
    __ABSTRACT__(bool operator()() const);
};

CUT_NS_END

#endif
