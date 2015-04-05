#include "magellan/startup/StartUp.h"
#include "magellan/auto/TestFactoryRegistry.h"
#include "magellan/core/TestRunner.h"
#include <memory>
#include <iostream>

MAGELLAN_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    auto suite = TestFactoryRegistry::makeAllTests();
    return TestRunner().run(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}

MAGELLAN_NS_END
