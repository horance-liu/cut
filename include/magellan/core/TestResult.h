#ifndef _7Q5LD8WDHIYD4YAN2MCI6W2EECFPWRMQK7TPIRTA7HRM7L83N1O5MX0               
#define _7Q5LD8WDHIYD4YAN2MCI6W2EECFPWRMQK7TPIRTA7HRM7L83N1O5MX0

#include <infra/base/Role.h>

MAGELLAN_NS_BEGIN

struct Test;
struct TestFunctor;

DEFINE_ROLE(TestResult)
{
    ABSTRACT(void startTest(const Test&));
    ABSTRACT(void endTest(const Test&));

    ABSTRACT(void startSuite(const Test&));
    ABSTRACT(void endSuite(const Test&));

    ABSTRACT(void runTest(const Test&));
    ABSTRACT(bool protect(const TestFunctor&, const Test&, const char* desc)); 
};

MAGELLAN_NS_END

#endif

