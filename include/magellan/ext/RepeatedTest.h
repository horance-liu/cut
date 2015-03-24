#ifndef HBB45B5B7_7E6D_4259_88E1_37CEC4BD7E7A
#define HBB45B5B7_7E6D_4259_88E1_37CEC4BD7E7A

#include <magellan/ext/TestDecorator.h>

MAGELLAN_NS_BEGIN

struct RepeatedTest : TestDecorator
{
    explicit RepeatedTest(Test& test, int times);

private:
    OVERRIDE(void run(TestResult&));
    OVERRIDE(int countTestCases() const);
    OVERRIDE(int countChildTests() const);

private:
    int times;
};

MAGELLAN_NS_END

#endif
