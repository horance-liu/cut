#ifndef H6DE28224_E43F_4689_BA39_491C30F80764
#define H6DE28224_E43F_4689_BA39_491C30F80764

#include "magellan/magellan.h"

MAGELLAN_NS_BEGIN

struct Test;

struct TestRunner
{
    bool run(Test*);
};

MAGELLAN_NS_END

#endif
