#ifndef _R2RGF94XEYGH3CTU7C57VEO4HSA4DG6RFRG0FRS2TOKTBMIYZM8SCDWP               
#define _R2RGF94XEYGH3CTU7C57VEO4HSA4DG6RFRG0FRS2TOKTBMIYZM8SCDWP

#include <magellan/infra/dci/Role.h>
#include <magellan/framework/base/magellan.h>

MAGELLAN_NS_BEGIN

DEFINE_ROLE(TestFunctor)
{
    ABSTRACT(bool operator()() const);
};

MAGELLAN_NS_END

#endif
