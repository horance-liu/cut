#include "magellan/core/TestRunner.h"
#include "magellan/core/TestResult.h"
#include "magellan/core/Test.h"
#include "magellan/listener/ResultPrinter.h"

MAGELLAN_NS_BEGIN

TestRunner::TestRunner(std::ostream& out)
  : out(out)
{
}

void TestRunner::run(Test* test)
{
    TestResult result;
    result.add(new ResultPrinter(out));
    result.runTest(*test);

    delete test;
}

MAGELLAN_NS_END
