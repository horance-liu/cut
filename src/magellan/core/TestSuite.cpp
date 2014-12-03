#include <magellan/core/TestSuite.h>
#include <magellan/core/TestResult.h>

MAGELLAN_NS_BEGIN

TestSuite::TestSuite(const std::string& name)
  : name(name)
{}

TestSuite::~TestSuite()
{
    for (auto test : tests)
    {
        delete test;
    }

    tests.clear();
}

void TestSuite::addTest(const Test& test)
{
    tests.push_back(&test);
}

const std::string& TestSuite::getName() const
{
    return name;
}

int TestSuite::getNumOfTestCases() const
{
    auto num = 0;

    for (auto test : tests)
    {
        num += test->getNumOfTestCases();
    }

    return num;
}

inline void TestSuite::doStartSuite(TestResult& result) const
{
    result.startSuite(*this);
}

inline void TestSuite::doEndSuite(TestResult& result) const
{
    result.endSuite(*this);
}

inline void TestSuite::doRunChildTests(TestResult& result) const
{
    for (auto test : tests)
    {
        test->run(result);
    }
}

void TestSuite::run(TestResult& result) const
{
    doStartSuite(result);
    doRunChildTests(result);
    doEndSuite(result);
}

MAGELLAN_NS_END

