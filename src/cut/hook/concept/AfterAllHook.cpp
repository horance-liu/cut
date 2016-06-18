#include <cut/hook/concept/AfterAllHook.h>
#include <cut/hook/runtime/Runtime.h>
#include <cut/hook/registry/HookRegistries.h>

CUT_NS_BEGIN

AfterAllHook::AfterAllHook()
{
    RUNTIME(AfterAllHookRegistry).add(*this);
}

CUT_NS_END
