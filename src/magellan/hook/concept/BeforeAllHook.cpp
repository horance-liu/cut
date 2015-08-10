#include <magellan/hook/concept/BeforeAllHook.h>
#include <magellan/hook/runtime/Runtime.h>
#include <magellan/hook/registry/HookRegistries.h>

MAGELLAN_NS_BEGIN

BeforeAllHook::BeforeAllHook()
{
    RUNTIME(BeforeAllHookRegistry).add(*this);
}

MAGELLAN_NS_END
