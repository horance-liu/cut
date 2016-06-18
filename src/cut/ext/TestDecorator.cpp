#include <cut/ext/TestDecorator.h>

CUT_NS_BEGIN

TestDecorator::TestDecorator(Test& test)
    : test(test)
{
}

void TestDecorator::run(TestResult& result)
{
    test.run(result);
}

int TestDecorator::countTestCases() const
{
    return test.countTestCases();
}

int TestDecorator::countChildTests() const
{
    return test.countChildTests();
}

const std::string& TestDecorator::getName () const
{
    return test.getName();
}

CUT_NS_END
