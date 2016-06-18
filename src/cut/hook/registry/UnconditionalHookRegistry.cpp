#include <cut/hook/registry/UnconditionalHookRegistry.h>
#include <cut/hook/concept/UnconditionalHook.h>

CUT_NS_BEGIN

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

CUT_NS_END
