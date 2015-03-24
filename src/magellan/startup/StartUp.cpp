#include "magellan/startup/StartUp.h"
#include "magellan/auto/TestFactoryRegistry.h"
#include "magellan/core/TestRunner.h"
#include <memory>
#include <iostream>

MAGELLAN_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    TestRunner().run(TestFactoryRegistry::makeAllTests());
    return 0;
}

MAGELLAN_NS_END
