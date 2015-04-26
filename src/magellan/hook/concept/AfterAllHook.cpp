#include <magellan/hook/concept/AfterAllHook.h>
#include <magellan/hook/runtime/Runtime.h>

MAGELLAN_NS_BEGIN

AfterAllHook::AfterAllHook()
{
    RUNTIME(AfterAllHookRegistry, registry);
    registry.add(*this);
}

MAGELLAN_NS_END
