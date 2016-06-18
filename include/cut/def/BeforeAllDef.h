#ifndef HF533895E_2995_47DD_B6B9_C8C1A2BDC0DB
#define HF533895E_2995_47DD_B6B9_C8C1A2BDC0DB

#include <cut/hook/registry/HookRegistration.h>
#include <cut/hook/concept/BeforeAllHook.h>

CUT_NS_BEGIN

#define BEFORE_ALL_OBJECT(object) UNCONDITIONAL_HOOK(object, BeforeAllHook)

///////////////////////////////////////////////////////////////
#define BEFORE_ALL() BEFORE_ALL_OBJECT(HOOK_NAME)

CUT_NS_END

#endif
