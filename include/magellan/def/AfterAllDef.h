#ifndef HEE848E6E_B290_486C_82DD_B24EACD74E19
#define HEE848E6E_B290_486C_82DD_B24EACD74E19

#include <magellan/hook/registry/HookRegistration.h>
#include <magellan/hook/concept/AfterAllHook.h>

MAGELLAN_NS_BEGIN

#define AFTER_ALL_OBJECT(object) UNCONDITIONAL_HOOK(object, AfterAllHook)

///////////////////////////////////////////////////////////////
#define AFTER_ALL() AFTER_ALL_OBJECT(HOOK_NAME)

MAGELLAN_NS_END

#endif
