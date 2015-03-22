#ifndef HC1529C5B_742D_4014_BBBF_7533B3E13905
#define HC1529C5B_742D_4014_BBBF_7533B3E13905

#include "magellan/framework/core/TestListener.h"

MAGELLAN_NS_BEGIN

struct TestProgressListener : TestListener
{
    OVERRIDE(void startTest(const Test&));
    OVERRIDE(void endTest(const Test&));

    OVERRIDE(void startSuite(const Test&));
    OVERRIDE(void endSuite(const Test&));

    OVERRIDE(void addFailure(const TestFailure&));
};

MAGELLAN_NS_END

#endif
