#include <cut/except/TestFailure.h>
#include <cut/core/Test.h>
#include <cut/core/TestFunctor.h>

CUT_NS_BEGIN

TestFailure::TestFailure(const TestFunctor& method, Message&& msg, bool failure)
  : test(method.__ROLE__(Test)), msg(std::move(msg)), failure(failure)
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

CUT_NS_END
