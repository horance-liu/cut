#ifndef H39E22C4F_D979_48F1_BB11_E3273F6AF684
#define H39E22C4F_D979_48F1_BB11_E3273F6AF684

#include <magellan/magellan.h>
#include <vector>

MAGELLAN_NS_BEGIN

struct UnconditionalHook;

struct UnconditionalHookRegistry
{
    void add(UnconditionalHook&);
    void execHooks();

private:
    std::vector<UnconditionalHook*> hooks;
};

MAGELLAN_NS_END

#endif
