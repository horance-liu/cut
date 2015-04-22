#include "magellan/startup/StartUp.h"
#include "magellan/auto/TestFactoryRegistry.h"
#include "magellan/core/TestRunner.h"
#include "magellan/options/MagellanOptions.h"

MAGELLAN_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    OPTIONS.capatureOptionsFrom(argc, (const char** )argv);

    if (OPTIONS.hasHelpOption())
    {
        OPTIONS.handlerHelpOption();
        return EXIT_SUCCESS;
    }

    auto suite = TestFactoryRegistry::makeAllTests();
    return TestRunner().run(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}

MAGELLAN_NS_END
