#include "magellan/startup/StartUp.h"
#include "magellan/auto/TestFactoryRegistry.h"
#include "magellan/core/TestRunner.h"
#include <magellan/core/TestOption.h>

MAGELLAN_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    TestOption& testOption = TestOption::getInstance();
    testOption.capatureOptionsFrom(argc, (const char** )argv);

    if (testOption.hasHelpOption())
    {
        testOption.handlerHelpOption();
        return EXIT_SUCCESS;
    }

    auto suite = TestFactoryRegistry::makeAllTests();
    return TestRunner().run(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}

MAGELLAN_NS_END
