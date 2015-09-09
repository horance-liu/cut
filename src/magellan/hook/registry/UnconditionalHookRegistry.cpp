#include <magellan/hook/registry/UnconditionalHookRegistry.h>
#include <magellan/hook/concept/UnconditionalHook.h>

MAGELLAN_NS_BEGIN

void UnconditionalHookRegistry::add(UnconditionalHook& hook)
{
    hooks.push_back(&hook);
}

void UnconditionalHookRegistry::execHooks()
{
    for(auto hook : hooks)
    {
        hook->invoke();
    }
}

MAGELLAN_NS_END
