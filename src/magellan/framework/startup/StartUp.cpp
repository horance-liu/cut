#include "magellan/framework/startup/StartUp.h"
#include "magellan/framework/auto/TestFactoryRegistry.h"
#include "magellan/framework/core/TestResult.h"
#include "magellan/framework/core/Test.h"
#include "magellan/framework/listener/TestProgressListener.h"
#include <memory>

MAGELLAN_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    TestFactory& factory = TestFactoryRegistry::getInstance();

    std::unique_ptr<Test> suite(factory.make());

    TestResult result;
    result.add(new TestProgressListener);

    suite->run(result);

    return 0;
}

MAGELLAN_NS_END
