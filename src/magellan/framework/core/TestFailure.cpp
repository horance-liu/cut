#include "magellan/framework/core/TestFailure.h"

MAGELLAN_NS_BEGIN

TestFailure::TestFailure(Test& test, const Message& msg, bool isError)
  : test(test), msg(msg), isError(isError)
{
}

MAGELLAN_NS_END
