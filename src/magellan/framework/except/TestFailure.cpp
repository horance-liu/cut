#include "magellan/framework/except/TestFailure.h"

MAGELLAN_NS_BEGIN

TestFailure::TestFailure(Test& test, const Message& msg, bool error)
  : test(test), msg(msg), error(error)
{
}

bool TestFailure::isError() const
{
    return error;
}

MAGELLAN_NS_END
