#include <magellan/hook/concept/BeforeAllHook.h>
#include <magellan/hook/runtime/Runtime.h>

MAGELLAN_NS_BEGIN

BeforeAllHook::BeforeAllHook()
{
    RUNTIME(BeforeAllHookRegistry, registry);
    registry.add(*this);
}

MAGELLAN_NS_END
