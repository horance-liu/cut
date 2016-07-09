#ifndef _SAOXDTVZ85W9YDU8WXPQZX5VG9GYC1PRD9KOOAOJADH827VEOLVORP2L               
#define _SAOXDTVZ85W9YDU8WXPQZX5VG9GYC1PRD9KOOAOJADH827VEOLVORP2L

#include <cui/dci/__Role__.h>
#include <cut/cut.h>

CUT_NS_BEGIN

struct Test;
struct TestResult;
struct TestFailure;

__TRAIT__(TestListener)
{
    __DEFAULT__(void, startTest(const Test&));
    __DEFAULT__(void, endTest(const Test&));
    
    __DEFAULT__(void, startSuite(const Test&));
    __DEFAULT__(void, endSuite(const Test&));
    
    __DEFAULT__(void, startTestRun(const Test&, TestResult&));
    __DEFAULT__(void, endTestRun(const Test&, TestResult&));
    
    __DEFAULT__(void, addFailure(const TestFailure&));
};

CUT_NS_END

#endif

