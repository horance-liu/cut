#include <cui/mem/__ScopeExit__.h>
#include <cut/core/TestRunner.h>
#include <cut/startup/TestOptions.h>
#include <cut/core/TestResult.h>
#include <cut/ext/RepeatedTest.h>
#include <cut/auto/TestFactorySuite.h>

CUT_NS_BEGIN

inline void TestRunner::addListeners(TestResult& result) const
{
    result.add(__ROLE__(TestOptions).makeTextPrinter());
    result.add(__ROLE__(TestOptions).makeXmlPrinter());
}

inline bool TestRunner::run(Test* test)
{
    __SCOPE_EXIT__([=]{ delete test; });
                        
    TestResult result;
    addListeners(result);

    RepeatedTest repeated(*test, __ROLE__(TestOptions).repeat());
    result.run(repeated);

    return result.isSucc();
}

bool TestRunner::run()
{
    TestFactory& factory = __ROLE__(TestFactorySuite);
    return run(factory.make());
}

CUT_NS_END
