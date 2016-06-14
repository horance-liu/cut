#ifndef _PC5J48M0RPLH5JKYMMM8L6D1OYJOPSXFI2OMJIPUIYK6KENE4W1SJSG9               
#define _PC5J48M0RPLH5JKYMMM8L6D1OYJOPSXFI2OMJIPUIYK6KENE4W1SJSG9

#include <ccinfra/dci/Role.h>
#include <magellan/magellan.h>

MAGELLAN_NS_BEGIN

struct Test;

DEFINE_ROLE(TestFactory)
{
    ABSTRACT(Test* make());
};

MAGELLAN_NS_END

#endif
