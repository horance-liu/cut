#include "magellan/core/TestRunner.h"
#include "magellan/core/TestResult.h"
#include "magellan/core/Test.h"
#include "l0-infra/std/ScopeExit.h"
#include "magellan/hook/runtime/Runtime.h"
#include "magellan/listener/ListenerFactory.h"
#include "magellan/startup/TestOptions.h"

MAGELLAN_NS_BEGIN

bool TestRunner::run(Test* test)
{
    SCOPE_EXIT([=]{ delete test; });
                        
    TestResult result;

    RUNTIME(ListenerFactory, listeners);
    RUNTIME(TestOptions, options);

    listeners.create(result);

    for(int i = 0; i< options.repeat(); ++i)
    {
    	result.runTest(*test);
    }
    return result.isSucc();
}

MAGELLAN_NS_END
