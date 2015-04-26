#ifndef _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5               
#define _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5

#include "magellan/auto/TestFactoryRegistry.h"
#include "magellan/auto/TestSuiteFactory.h"
#include "magellan/hook/runtime/Runtime.h"

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct AutoTestSuite
{
    AutoTestSuite()
    {
        __RUNTIME__(TestFactoryRegistry).addFactory(factory);
    }

private:
    TestSuiteFactory<Fixture> factory;
};

MAGELLAN_NS_END

#endif
