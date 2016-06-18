#ifndef H4F0DAA73_78BC_4665_B214_D485ED463BB1
#define H4F0DAA73_78BC_4665_B214_D485ED463BB1

#include <cub/dci/Role.h>
#include <cut/cut.h>

CUT_NS_BEGIN

struct BeforeAllHookRegistry;
struct AfterAllHookRegistry;
struct TestFactorySuite;
struct TestOptions;
struct TestRunner;

DEFINE_ROLE(Runtime)
{
    static Runtime& getIntance();

    HAS_ROLE(BeforeAllHookRegistry);
    HAS_ROLE(AfterAllHookRegistry);
    HAS_ROLE(TestFactorySuite);
    HAS_ROLE(TestOptions);
    HAS_ROLE(TestRunner);
};

#define RUNTIME(type) Runtime::getIntance().ROLE(type)

CUT_NS_END

#endif
