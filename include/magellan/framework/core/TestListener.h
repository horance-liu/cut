#ifndef _SAOXDTVZ85W9YDU8WXPQZX5VG9GYC1PRD9KOOAOJADH827VEOLVORP2L               
#define _SAOXDTVZ85W9YDU8WXPQZX5VG9GYC1PRD9KOOAOJADH827VEOLVORP2L

#include <magellan/infra/dci/Role.h>
#include <magellan/framework/magellan.h>

MAGELLAN_NS_BEGIN

struct Test;
struct TestResult;
struct TestFailure;

DEFINE_ROLE(TestListener)
{
    DEFAULT(void, startTest(Test&));
    DEFAULT(void, endTest(Test&));
    
    DEFAULT(void, startSuite(Test&));
    DEFAULT(void, endSuite(Test&));
    
    DEFAULT(void, startTestRun(Test&, TestResult&));
    DEFAULT(void, endTestRun(Test&, TestResult&));
    
    DEFAULT(void, addFailure(Test&, const TestFailure&));
    DEFAULT(void, addError(Test&, const TestFailure&));
};

MAGELLAN_NS_END

#endif

