#ifndef _R2RGF94XEYGH3CTU7C57VEO4HSA4DG6RFRG0FRS2TOKTBMIYZM8SCDWP               
#define _R2RGF94XEYGH3CTU7C57VEO4HSA4DG6RFRG0FRS2TOKTBMIYZM8SCDWP

#include <cub/dci/Role.h>
#include <cut/cut.h>

CUT_NS_BEGIN

struct Test;

DEFINE_ROLE(TestFunctor)
{
    HAS_ROLE(Test);
    ABSTRACT(bool operator()() const);
};

CUT_NS_END

#endif
