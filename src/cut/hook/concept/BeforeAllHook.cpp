#include <cut/hook/concept/BeforeAllHook.h>
#include <cut/hook/runtime/Runtime.h>
#include <cut/hook/registry/HookRegistries.h>

CUT_NS_BEGIN

BeforeAllHook::BeforeAllHook()
{
    RUNTIME(BeforeAllHookRegistry).add(*this);
}

CUT_NS_END
