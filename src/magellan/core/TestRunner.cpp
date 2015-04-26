#include "magellan/core/TestRunner.h"
#include "magellan/core/TestResult.h"
#include "magellan/core/Test.h"
#include "magellan/listener/text/TextResultPrinter.h"
#include "l0-infra/std/ScopeExit.h"

MAGELLAN_NS_BEGIN

TestRunner::TestRunner(std::ostream& out)
  : out(out)
{
}

bool TestRunner::run(Test* test)
{
    SCOPE_EXIT([=]{ delete test; });
                        
    TestResult result;
    result.add(new TextResultPrinter(out));

    result.runTest(*test);
    return result.isSucc();
}

MAGELLAN_NS_END
