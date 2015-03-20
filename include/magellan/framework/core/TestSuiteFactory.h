#ifndef _USDKQQD1YGIEJVTX87VTYCRVA9PSLATI4D280Q0SW0CUGGW4WG1Q2UO2               
#define _USDKQQD1YGIEJVTX87VTYCRVA9PSLATI4D280Q0SW0CUGGW4WG1Q2UO2

#include "magellan/framework/core/MetaTestFixture.h"
#include "magellan/framework/core/TestFactory.h"

MAGELLAN_NS_BEGIN

template <typename Fixture>
struct TestSuiteFactory : TestFactory
{
    OVERRIDE(Test* make())
    {
        static Fixture fixture;   // auto register all test method to MetaTestFixture<Fixture>

        return MetaTestFixture<Fixture>::suite();
    }
};

MAGELLAN_NS_END

#endif
