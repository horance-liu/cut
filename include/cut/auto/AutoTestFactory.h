#ifndef _USDKQQD1YGIEJVTX87VTYCRVA9PSLATI4D280Q0SW0CUGGW4WG1Q2UO2               
#define _USDKQQD1YGIEJVTX87VTYCRVA9PSLATI4D280Q0SW0CUGGW4WG1Q2UO2

#include <cut/auto/MetaTestFixture.h>
#include <cut/core/TestFactory.h>

CUT_NS_BEGIN

template <typename Fixture>
struct AutoTestFactory : TestFactory
{
private:
    __OVERRIDE__(Test* make())
    {
        // !!! auto register all test methods to MetaTestFixture<Fixture>
        static Fixture fixture;
        return MetaTestFixture<Fixture>::suite();
    }
};

CUT_NS_END

#endif
