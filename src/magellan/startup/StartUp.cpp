#include "magellan/startup/StartUp.h"
#include "magellan/startup/TestOptions.h"
#include "magellan/hook/runtime/Runtime.h"

MAGELLAN_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    RUNTIME(TestOptions).parse(argc, (const char**)argv);
    return RUNTIME(TestOptions).run();
}

MAGELLAN_NS_END
