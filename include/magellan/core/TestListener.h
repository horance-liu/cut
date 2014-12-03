#ifndef _SAOXDTVZ85W9YDU8WXPQZX5VG9GYC1PRD9KOOAOJADH827VEOLVORP2L               
#define _SAOXDTVZ85W9YDU8WXPQZX5VG9GYC1PRD9KOOAOJADH827VEOLVORP2L

#include <infra/base/Role.h>

MAGELLAN_NS_BEGIN

struct Test;
struct TestResult;
struct TestFailure;

DEFINE_ROLE(TestListener)
{
    DEFUALT(void, startTest(const Test&));
    DEFUALT(void, endTest(const Test&));
    
    DEFUALT(void, startSuite(const Test&));
    DEFUALT(void, endSuite(const Test&));
    
    DEFUALT(void, startTestRun(const Test&, TestResult&));
    DEFUALT(void, endTestRun(const Test&, TestResult&));
    
    DEFUALT(void, addFailure(const TestFailure&));
};

MAGELLAN_NS_END

#endif

