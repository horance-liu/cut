#ifndef _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5               
#define _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5

#include <magellan/auto/AutoTestFactory.h>
#include "magellan/auto/TestFactorySuite.h"
#include "magellan/hook/runtime/Runtime.h"

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct AutoTestSuite
{
    AutoTestSuite()
    {
        RUNTIME(TestFactorySuite).addFactory(factory);
    }

private:
    AutoTestFactory<Fixture> factory;
};

MAGELLAN_NS_END

#endif
