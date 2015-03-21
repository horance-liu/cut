#include "magellan/framework/core/TestProgressListener.h"
#include "magellan/framework/core/Test.h"
#include "magellan/framework/core/TestFailure.h"
#include <iostream>

MAGELLAN_NS_BEGIN

void TestProgressListener::startTest(Test& test)
{
    std::cout << "start: " << test.getName() << std::endl;
}

void TestProgressListener::endTest(Test& test)
{
    std::cout << "end: " << test.getName() << std::endl;
}

void TestProgressListener::startSuite(Test& test)
{
    std::cout << "start: " << test.getName() << std::endl;
}

void TestProgressListener::endSuite(Test& test)
{
    std::cout << "end: " << test.getName() << std::endl;
}

void TestProgressListener::startTestRun(Test& test, TestResult&)
{
    std::cout << "start: " << test.getName() << std::endl;
}

void TestProgressListener::endTestRun(Test& test, TestResult&)
{
    std::cout << "end: " << test.getName() << std::endl;
}

void TestProgressListener::addFailure(Test& test, const TestFailure& fail)
{
    std::cout << "fail: " << test.getName() << (fail.isError() ? "E" : "F") << std::endl;
}

void TestProgressListener::addError(Test& test, const TestFailure& fail)
{
    std::cout << "fail: " << test.getName() << (fail.isError() ? "E" : "F") << std::endl;
}

MAGELLAN_NS_END
