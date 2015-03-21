#ifndef HC1529C5B_742D_4014_BBBF_7533B3E13905
#define HC1529C5B_742D_4014_BBBF_7533B3E13905

#include "magellan/framework/core/TestListener.h"

MAGELLAN_NS_BEGIN

struct TestProgressListener : TestListener
{
    OVERRIDE(void startTest(Test&));
    OVERRIDE(void endTest(Test&));

    OVERRIDE(void startSuite(Test&));
    OVERRIDE(void endSuite(Test&));

    OVERRIDE(void startTestRun(Test&, TestResult&));
    OVERRIDE(void endTestRun(Test&, TestResult&));

    OVERRIDE(void addFailure(Test&, const TestFailure&));
    OVERRIDE(void addError(Test&, const TestFailure&));
};

MAGELLAN_NS_END

#endif
