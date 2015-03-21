#include "magellan/framework/core/StartUp.h"
#include "magellan/framework/core/TestFactoryRegistry.h"
#include "magellan/framework/core/TestResult.h"
#include "magellan/framework/core/Test.h"
#include "magellan/framework/core/TestProgressListener.h"
#include <memory>

MAGELLAN_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    TestFactory& factory = TestFactoryRegistry::getInstance();

    std::unique_ptr<Test> tests(factory.make());

    TestResult result;
    result.add(new TestProgressListener);

    tests->run(result);

    return 0;
}

MAGELLAN_NS_END
