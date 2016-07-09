#ifndef H6A8AA0FD_F336_493F_9E77_767862365287
#define H6A8AA0FD_F336_493F_9E77_767862365287

#include <cui/utils/__Symbol__.h>
#include <cut/cut.h>

CUT_NS_BEGIN

#define HOOK_NAME __UNIQUE_NAME__(HookObject)

///////////////////////////////////////////////////////////////
#define UNCONDITIONAL_HOOK(class_name, parent_class) \
struct class_name : parent_class       \
{                                                \
    class_name() {}                              \
                                                 \
private:                                         \
    __OVERRIDE__(void invoke());                     \
};                                               \
const class_name var##class_name;                \
void class_name::invoke()

CUT_NS_END

#endif
