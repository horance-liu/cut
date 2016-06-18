#ifndef HEE848E6E_B290_486C_82DD_B24EACD74E19
#define HEE848E6E_B290_486C_82DD_B24EACD74E19

#include <cut/hook/registry/HookRegistration.h>
#include <cut/hook/concept/AfterAllHook.h>

CUT_NS_BEGIN

#define AFTER_ALL_OBJECT(object) UNCONDITIONAL_HOOK(object, AfterAllHook)

///////////////////////////////////////////////////////////////
#define AFTER_ALL() AFTER_ALL_OBJECT(HOOK_NAME)

CUT_NS_END

#endif
