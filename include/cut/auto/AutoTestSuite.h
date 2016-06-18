#ifndef _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5               
#define _U4ZNOKCW5S5QFUOBAYJ90GPKBA7B4SC63V7LDGBMZSZHZFSL9V9YD7N5

#include <cut/auto/AutoTestFactory.h>
#include <cut/auto/TestFactorySuite.h>
#include <cut/hook/runtime/Runtime.h>

CUT_NS_BEGIN

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

CUT_NS_END

#endif
