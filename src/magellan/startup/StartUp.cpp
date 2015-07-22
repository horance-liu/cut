#include "magellan/startup/StartUp.h"
#include "magellan/auto/TestFactoryRegistry.h"
#include "magellan/core/TestRunner.h"
#include "magellan/startup/TestOptions.h"
#include "magellan/hook/runtime/Runtime.h"
#include <stdlib.h>

MAGELLAN_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    RUNTIME(TestOptions, options);

    options.parse(argc, (const char** )argv);

    TestFactory& factory = __RUNTIME__(TestFactoryRegistry);
    return TestRunner().run(factory.make()) ? EXIT_SUCCESS : EXIT_FAILURE;
}

MAGELLAN_NS_END
