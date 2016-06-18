#include <cut/startup/StartUp.h>
#include <cut/startup/TestOptions.h>
#include <cut/hook/runtime/Runtime.h>

CUT_NS_BEGIN

int run_all_tests(int argc, char** argv)
{
    RUNTIME(TestOptions).parse(argc, (const char**)argv);
    return RUNTIME(TestOptions).run();
}

CUT_NS_END
