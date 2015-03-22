#include "magellan/framework/except/TestFailure.h"
#include "magellan/framework/core/Test.h"

MAGELLAN_NS_BEGIN

TestFailure::TestFailure(const Test& test, const Message& msg, bool failture)
  : test(test), msg(msg), failture(failture)
{
}

bool TestFailure::isFailure() const
{
    return failture;
}

const std::string& TestFailure::getTestName() const
{
    return test.getName();
}

std::string TestFailure::getExceptionMsg() const
{
    return msg.str();
}

MAGELLAN_NS_END
