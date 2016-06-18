#include <cut/core/TestSuite.h>
#include <cut/core/TestResult.h>
#include <cub/algo/range.h>

CUT_NS_BEGIN

TestSuite::TestSuite(const std::string& name)
  : name(name)
{}

TestSuite::~TestSuite()
{
    cub::each(tests, [](Test* t){ delete t; });
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
    return cub::reduce(tests, 0, [](int& num, Test* test) {
        num += test->countTestCases();
    });
}

int TestSuite::countChildTests() const
{
    return (int)tests.size();
}

void TestSuite::runBare(TestResult &result)
{
    cub::each(tests, [&](Test* test){ test->run(result); });
}

void TestSuite::run(TestResult& result)
{
    result.run(*this);
}

CUT_NS_END

