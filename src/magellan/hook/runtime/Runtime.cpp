#include <magellan/hook/runtime/Runtime.h>

MAGELLAN_NS_BEGIN

namespace
{
    struct RuntimeImpl : Runtime
    {
    private:
        IMPL_ROLE_WITH_ROLE_VAR(BeforeAllHookRegistry);
        IMPL_ROLE_WITH_ROLE_VAR(AfterAllHookRegistry);
    };
}

Runtime& Runtime::getIntance()
{
    static RuntimeImpl runtime;
    return runtime;
}

MAGELLAN_NS_END
