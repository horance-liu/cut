#ifndef H4F0DAA73_78BC_4665_B214_D485ED463BB1
#define H4F0DAA73_78BC_4665_B214_D485ED463BB1

#include <cui/dci/__Role__.h>
#include <cut/cut.h>

CUT_NS_BEGIN

struct BeforeAllHookRegistry;
struct AfterAllHookRegistry;
struct TestFactorySuite;
struct TestOptions;
struct TestRunner;

__TRAIT__(Runtime)
{
    static Runtime& getIntance();

    __HAS_ROLE__(BeforeAllHookRegistry);
    __HAS_ROLE__(AfterAllHookRegistry);
    __HAS_ROLE__(TestFactorySuite);
    __HAS_ROLE__(TestOptions);
    __HAS_ROLE__(TestRunner);
};

#define RUNTIME(type) Runtime::getIntance().__ROLE__(type)

CUT_NS_END

#endif
