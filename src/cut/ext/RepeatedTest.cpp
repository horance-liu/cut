#include <cut/ext/RepeatedTest.h>

CUT_NS_BEGIN

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

int RepeatedTest::countChildTests() const
{
    return TestDecorator::countChildTests() * times;
}

CUT_NS_END
