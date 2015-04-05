#ifndef HC3CC1158_A7D9_4CDF_86FA_347EE268638E
#define HC3CC1158_A7D9_4CDF_86FA_347EE268638E

#include "magellan/core/TestListener.h"
#include "magellan/listener/util/Timer.h"
#include <stack>

MAGELLAN_NS_BEGIN

struct XmlResultPrinter : TestListener
{
    XmlResultPrinter();
    ~XmlResultPrinter();

private:
    OVERRIDE(void startTestRun(const Test&, TestResult&));
    OVERRIDE(void endTestRun(const Test&, TestResult&));

    OVERRIDE(void startSuite(const Test&));
    OVERRIDE(void endSuite(const Test&));

    OVERRIDE(void startTest(const Test&));
    OVERRIDE(void endTest(const Test&));

    OVERRIDE(void addFailure(const TestFailure&));
};

MAGELLAN_NS_END

#endif
