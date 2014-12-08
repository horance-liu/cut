#include <magellan/ext/RepeatedTest.h>

MAGELLAN_NS_BEGIN

RepeatedTest::RepeatedTest(Test& test, int times)
    : TestDecorator(test), times(times)
{
}

void RepeatedTest::run(TestResult& result)
{
    for(int i = 0; i < times; i++)
    {
        TestDecorator::run(result);
    }
}

int RepeatedTest::countTestCases() const
{
    return TestDecorator::countTestCases() * times;
}

MAGELLAN_NS_END
