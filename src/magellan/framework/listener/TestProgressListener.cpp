#include "magellan/framework/listener/TestProgressListener.h"
#include "magellan/framework/core/Test.h"
#include "magellan/framework/except/TestFailure.h"
#include <iostream>

MAGELLAN_NS_BEGIN

void TestProgressListener::startTest(const Test& test)
{
    std::cout << "start test: " << test.getName() << std::endl;
}

void TestProgressListener::endTest(const Test& test)
{
    std::cout << "end test: " << test.getName() << std::endl;
}

void TestProgressListener::startSuite(const Test& test)
{
    std::cout << "start suite: " << test.getName() << std::endl;
}

void TestProgressListener::endSuite(const Test& test)
{
    std::cout << "end suite: " << test.getName() << std::endl;
}

void TestProgressListener::addFailure(const TestFailure& fail)
{
    std::cout << "fail: " << fail.getTestName() << "["
              << (fail.isFailure() ? "F" : "E") << "]\n"
              << fail.getExceptionMsg();
}

MAGELLAN_NS_END
