#include "magellan/core/TestRunner.h"
#include "magellan/startup/TestOptions.h"
#include "magellan/core/TestResult.h"
#include "magellan/ext/RepeatedTest.h"
#include "magellan/auto/TestFactorySuite.h"
#include "l0-infra/std/ScopeExit.h"

MAGELLAN_NS_BEGIN

inline void TestRunner::addListeners(TestResult& result) const
{
    result.add(ROLE(TestOptions).makeTextPrinter());
    result.add(ROLE(TestOptions).makeXmlPrinter());
}

inline bool TestRunner::run(Test* test)
{
    SCOPE_EXIT([=]{ delete test; });
                        
    TestResult result;
    addListeners(result);

    RepeatedTest repeated(*test, ROLE(TestOptions).repeat());
    result.run(repeated);

    return result.isSucc();
}

bool TestRunner::run()
{
    TestFactory& factory = ROLE(TestFactorySuite);
    return run(factory.make());
}

MAGELLAN_NS_END
