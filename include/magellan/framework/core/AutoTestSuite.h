#ifndef _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5               
#define _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5

#include "magellan/framework/core/TestFactoryRegistry.h"
#include "magellan/framework/core/TestSuiteFactory.h"

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct AutoTestSuite
{
    AutoTestSuite()
    {
        TestFactoryRegistry::getInstance().addFactory(factory);
    }

private:
    TestSuiteFactory<Fixture> factory;
};

MAGELLAN_NS_END

#endif
