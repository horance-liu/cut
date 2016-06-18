#ifndef HAF194D9D_8BA9_43F2_8E01_02B894CBA3E7
#define HAF194D9D_8BA9_43F2_8E01_02B894CBA3E7

#include <cut/core/TestListener.h>
#include <iostream>

CUT_NS_BEGIN

struct ProgressPrinter : TestListener
{
    ProgressPrinter(std::ostream& = std::cout);

private:
    OVERRIDE(void startTest(const Test&));
    OVERRIDE(void endTestRun(const Test&, TestResult&));
    OVERRIDE(void addFailure(const TestFailure&));

private:
    std::ostream& out;
};

CUT_NS_END

#endif
