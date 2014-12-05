#include <magellan/core/TestSuite.h>
#include <magellan/core/TestResult.h>
#include <infra/base/Collections.h>


MAGELLAN_NS_BEGIN

TestSuite::TestSuite(const std::string& name)
  : name(name)
{}

TestSuite::~TestSuite()
{
    clear_container(tests);
}

void TestSuite::addTest(Test* test)
{
    tests.push_back(test);
}

const std::string& TestSuite::getName() const
{
    return name;
}

int TestSuite::countTestCases() const
{
    auto num = 0;

    for (auto test : tests)
    {
        num += test->countTestCases();
    }

    return num;
}

void TestSuite::runBare(TestResult &result)
{
    for (auto test : tests)
    {
        test->run(result);
    }
}

void TestSuite::run(TestResult& result)
{
    result.run(*this);
}

MAGELLAN_NS_END

