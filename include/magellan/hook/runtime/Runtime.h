#ifndef H4F0DAA73_78BC_4665_B214_D485ED463BB1
#define H4F0DAA73_78BC_4665_B214_D485ED463BB1

#include <l0-infra/dci/Role.h>
#include <magellan/hook/registry/HookRegistries.h>

MAGELLAN_NS_BEGIN

DEFINE_ROLE(Runtime)
{
    static Runtime& getIntance();

    HAS_ROLE(BeforeAllHookRegistry);
    HAS_ROLE(AfterAllHookRegistry);
};

#define REGISTRY(type, name) type& name = Runtime::getIntance().ROLE(type)

MAGELLAN_NS_END

#endif
