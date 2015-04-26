#include "magellan/hook/runtime/Runtime.h"
#include "magellan/auto/TestFactoryRegistry.h"
#include "magellan/hook/registry/HookRegistries.h"
#include "magellan/startup/TestOptions.h"

MAGELLAN_NS_BEGIN

namespace
{
    struct RuntimeImpl
        : private BeforeAllHookRegistry
        , private AfterAllHookRegistry
        , private TestFactoryRegistry
        , private TestOptions
        , Runtime
    {
        IMPL_ROLE(BeforeAllHookRegistry);
        IMPL_ROLE(AfterAllHookRegistry);
        IMPL_ROLE(TestFactoryRegistry);
        IMPL_ROLE(TestOptions);
    };
}

Runtime& Runtime::getIntance()
{
    static RuntimeImpl runtime;
    return runtime;
}

MAGELLAN_NS_END
