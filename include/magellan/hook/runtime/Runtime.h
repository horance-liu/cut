#ifndef H4F0DAA73_78BC_4665_B214_D485ED463BB1
#define H4F0DAA73_78BC_4665_B214_D485ED463BB1

#include <l0-infra/dci/Role.h>
#include <magellan/hook/registry/HookRegistries.h>

MAGELLAN_NS_BEGIN

struct BeforeAllHookRegistry;
struct AfterAllHookRegistry;
struct TestFactoryRegistry;
struct TestOptions;

DEFINE_ROLE(Runtime)
{
    static Runtime& getIntance();

    HAS_ROLE(BeforeAllHookRegistry);
    HAS_ROLE(AfterAllHookRegistry);
    HAS_ROLE(TestFactoryRegistry);
    HAS_ROLE(TestOptions);
};

#define __RUNTIME__(type) Runtime::getIntance().ROLE(type)
#define RUNTIME(type, name) type& name = __RUNTIME__(type)

MAGELLAN_NS_END

#endif
