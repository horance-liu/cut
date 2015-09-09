#ifndef HAF194D9D_8BA9_43F2_8E01_02B894CBA3E7
#define HAF194D9D_8BA9_43F2_8E01_02B894CBA3E7

#include "magellan/core/TestListener.h"
#include <iostream>

MAGELLAN_NS_BEGIN

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

MAGELLAN_NS_END

#endif
