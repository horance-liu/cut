#include <cut/hook/runtime/Runtime.h>
#include <cut/auto/TestFactorySuite.h>
#include <cut/hook/registry/HookRegistries.h>
#include <cut/startup/TestOptions.h>
#include <cut/core/TestRunner.h>

CUT_NS_BEGIN

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
        __IMPL_ROLE__(BeforeAllHookRegistry);
        __IMPL_ROLE__(AfterAllHookRegistry);
        __IMPL_ROLE__(TestFactorySuite);
        __IMPL_ROLE__(TestOptions);
        __IMPL_ROLE__(TestRunner);
    };
}

Runtime& Runtime::getIntance()
{
    static RuntimeImpl runtime;
    return runtime;
}

CUT_NS_END
