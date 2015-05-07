#ifndef LISTENERFACTORY_Mon_Apr_27_22_32_38_2015_H
#define LISTENERFACTORY_Mon_Apr_27_22_32_38_2015_H

#include <magellan/magellan.h>

MAGELLAN_NS_BEGIN

struct TestResult;

struct ListenerFactory
{
    void create(TestResult&);
};

MAGELLAN_NS_END

#endif
