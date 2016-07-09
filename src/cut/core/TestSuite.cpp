#include <cui/algo/__range__.h>
#include <cut/core/TestSuite.h>
#include <cut/core/TestResult.h>

CUT_NS_BEGIN

TestSuite::TestSuite(const std::string& name)
  : name(name)
{}

TestSuite::~TestSuite()
{
    cui::each(tests, [](Test* t){ delete t; });
}

void TestSuite::addTest(Test* test)
{
    if (test != 0)
    {
        tests.push_back(test);
    }
}

const std::string& TestSuite::getName() const
{
    return name;
}

int TestSuite::countTestCases() const
{
    return cui::reduce(tests, 0, [](int& num, Test* test) {
        num += test->countTestCases();
    });
}

int TestSuite::countChildTests() const
{
    return (int)tests.size();
}

void TestSuite::runBare(TestResult &result)
{
    cui::each(tests, [&](Test* test){ test->run(result); });
}

void TestSuite::run(TestResult& result)
{
    result.run(*this);
}

CUT_NS_END

