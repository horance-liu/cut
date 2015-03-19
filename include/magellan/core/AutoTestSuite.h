#ifndef _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5               
#define _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5

#include <magellan/base/magellan.h>

MAGELLAN_NS_BEGIN


template <typename Fixture>
struct AutoTestSuite
{
    AutoTestSuite() : registry(TestFactoryRegistry::getRegistry())
    {
        registry.addFactory(factory);
    }

private:
    TestFactoryRegistry& registry;
    TestFactorySuite<Fixture> factory;
};

MAGELLAN_NS_END

#endif
