#ifndef _SAOXDTVZ85W9YDU8WXPQZX5VG9GYC1PRD9KOOAOJADH827VEOLVORP2L               
#define _SAOXDTVZ85W9YDU8WXPQZX5VG9GYC1PRD9KOOAOJADH827VEOLVORP2L

#include <cub/dci/Role.h>
#include <magellan/magellan.h>

MAGELLAN_NS_BEGIN

struct Test;
struct TestResult;
struct TestFailure;

DEFINE_ROLE(TestListener)
{
    DEFAULT(void, startTest(const Test&));
    DEFAULT(void, endTest(const Test&));
    
    DEFAULT(void, startSuite(const Test&));
    DEFAULT(void, endSuite(const Test&));
    
    DEFAULT(void, startTestRun(const Test&, TestResult&));
    DEFAULT(void, endTestRun(const Test&, TestResult&));
    
    DEFAULT(void, addFailure(const TestFailure&));
};

MAGELLAN_NS_END

#endif

