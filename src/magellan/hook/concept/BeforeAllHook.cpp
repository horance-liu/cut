#include <magellan/hook/concept/BeforeAllHook.h>
#include <magellan/hook/runtime/Runtime.h>

MAGELLAN_NS_BEGIN

BeforeAllHook::BeforeAllHook()
{
    REGISTRY(BeforeAllHookRegistry, registry);
    registry.add(*this);
}

MAGELLAN_NS_END
