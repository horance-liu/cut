#include "magellan/hook/runtime/Runtime.h"
#include "magellan/auto/TestFactorySuite.h"
#include "magellan/hook/registry/HookRegistries.h"
#include "magellan/startup/TestOptions.h"
#include "magellan/core/TestRunner.h"

MAGELLAN_NS_BEGIN

namespace
{
    struct RuntimeImpl
        : private BeforeAllHookRegistry
        , private AfterAllHookRegistry
        , private TestFactorySuite
        , private TestOptions
        , private TestRunner
        , Runtime
    {
    private:
        IMPL_ROLE(BeforeAllHookRegistry);
        IMPL_ROLE(AfterAllHookRegistry);
        IMPL_ROLE(TestFactorySuite);
        IMPL_ROLE(TestOptions);
        IMPL_ROLE(TestRunner);
    };
}

Runtime& Runtime::getIntance()
{
    static RuntimeImpl runtime;
    return runtime;
}

MAGELLAN_NS_END
