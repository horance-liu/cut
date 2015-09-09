#include "magellan/core/TestSuite.h"
#include "magellan/core/TestResult.h"
#include <l0-infra/std/Algorithm.h>

MAGELLAN_NS_BEGIN

TestSuite::TestSuite(const std::string& name)
  : name(name)
{}

TestSuite::~TestSuite()
{
    stdext::each(tests, [](Test* t){ delete t; });
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
    return stdext::reduce(tests, 0, [](int& num, Test* test) {
        num += test->countTestCases();
    });
}

int TestSuite::countChildTests() const
{
    return (int)tests.size();
}

void TestSuite::runBare(TestResult &result)
{
    stdext::each(tests, [&](Test* test){ test->run(result); });
}

void TestSuite::run(TestResult& result)
{
    result.run(*this);
}

bool TestSuite::hasChild() const
{
    return countChildTests() != 0;
}

MAGELLAN_NS_END

