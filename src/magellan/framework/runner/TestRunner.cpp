#include "magellan/framework/runner/TestRunner.h"
#include "magellan/framework/listener/ResultPrinter.h"
#include "magellan/framework/core/TestResult.h"
#include "magellan/framework/core/Test.h"

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
