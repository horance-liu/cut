#ifndef H6A8AA0FD_F336_493F_9E77_767862365287
#define H6A8AA0FD_F336_493F_9E77_767862365287

#include <magellan/magellan.h>
#include <ccinfra/base/Symbol.h>

MAGELLAN_NS_BEGIN

#define HOOK_NAME UNIQUE_NAME(HookObject)

///////////////////////////////////////////////////////////////
#define UNCONDITIONAL_HOOK(class_name, parent_class) \
struct class_name : parent_class       \
{                                                \
    class_name() {}                              \
                                                 \
private:                                         \
    OVERRIDE(void invoke());                     \
};                                               \
const class_name var##class_name;                \
void class_name::invoke()

MAGELLAN_NS_END

#endif
