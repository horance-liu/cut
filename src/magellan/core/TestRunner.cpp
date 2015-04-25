#include "magellan/core/TestRunner.h"
#include "magellan/core/TestResult.h"
#include "magellan/core/Test.h"
#include "magellan/listener/text/TextResultPrinter.h"
#include "l0-infra/std/ScopeExit.h"
#include "magellan/listener/xml/XmlResultPrinter.h"
#include "magellan/options/MagellanOptions.h"


MAGELLAN_NS_BEGIN

TestRunner::TestRunner(std::ostream& out)
  : out(out)
{
}

bool TestRunner::run(Test* test)
{
    SCOPE_EXIT([=]{ delete test; });

    TestListener* listeners[] ={new TextResultPrinter(out)
                                , []{return OPTIONS.outPutXml()? new XmlResultPrinter() : 0;}()};
                        
    TestResult result;
    for(auto& var: listeners)
    {
        result.add(var);
    }

    result.runTest(*test);

    return result.isSucc();
}

MAGELLAN_NS_END
