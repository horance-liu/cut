#ifndef HBB45B5B7_7E6D_4259_88E1_37CEC4BD7E7A
#define HBB45B5B7_7E6D_4259_88E1_37CEC4BD7E7A

#include <cut/ext/TestDecorator.h>

CUT_NS_BEGIN

struct RepeatedTest : TestDecorator
{
    RepeatedTest(Test& test, int times);

private:
    __OVERRIDE__(void run(TestResult&));
    __OVERRIDE__(int countTestCases() const);
    __OVERRIDE__(int countChildTests() const);

private:
    int times;
};

CUT_NS_END

#endif
