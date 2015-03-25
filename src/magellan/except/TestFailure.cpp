#include "magellan/except/TestFailure.h"
#include "magellan/core/Test.h"
#include "magellan/core/TestFunctor.h"

MAGELLAN_NS_BEGIN

TestFailure::TestFailure(const TestFunctor& method, Message&& msg, bool failure)
  : test(method.ROLE(Test)), msg(std::move(msg)), failure(failure)
{}

bool TestFailure::isFailure() const
{
    return failure;
}

const std::string& TestFailure::getTestName() const
{
    return test.getName();
}

const std::string& TestFailure::getExceptionMsg() const
{
    return msg.str();
}

MAGELLAN_NS_END
