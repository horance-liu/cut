#include <cut/core/TestRunner.h>
#include <cut/startup/TestOptions.h>
#include <cut/core/TestResult.h>
#include <cut/ext/RepeatedTest.h>
#include <cut/auto/TestFactorySuite.h>
#include <cub/mem/ScopeExit.h>

CUT_NS_BEGIN

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

CUT_NS_END
