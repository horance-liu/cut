#include <magellan/hook/concept/AfterAllHook.h>
#include <magellan/hook/runtime/Runtime.h>
#include <magellan/hook/registry/HookRegistries.h>

MAGELLAN_NS_BEGIN

AfterAllHook::AfterAllHook()
{
    RUNTIME(AfterAllHookRegistry).add(*this);
}

MAGELLAN_NS_END
