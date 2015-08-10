#include "magellan/startup/StartUp.h"
#include "magellan/core/TestRunner.h"
#include "magellan/hook/runtime/Runtime.h"
#include <stdlib.h>

MAGELLAN_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    return RUNTIME(TestRunner).run(argc, (const char**)argv)
        ? EXIT_SUCCESS : EXIT_FAILURE;
}

MAGELLAN_NS_END
