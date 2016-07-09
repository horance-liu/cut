#ifndef HC1529C5B_742D_4014_BBBF_7533B3E13905
#define HC1529C5B_742D_4014_BBBF_7533B3E13905

#include <cut/core/TestListener.h>
#include <iostream>
#include <stack>
#include <time.h>

CUT_NS_BEGIN

struct TestInfo;

struct TextResultPrinter : TestListener
{
    TextResultPrinter(std::ostream& = std::cout);
    ~TextResultPrinter();

private:
    __OVERRIDE__(void startTestRun(const Test&, TestResult&));
    __OVERRIDE__(void endTestRun(const Test&, TestResult&));

    __OVERRIDE__(void startSuite(const Test&));
    __OVERRIDE__(void endSuite(const Test&));

    __OVERRIDE__(void startTest(const Test&));
    __OVERRIDE__(void endTest(const Test&));

    __OVERRIDE__(void addFailure(const TestFailure&));

private:
    void onTestSucc(const Test& test);
    void onTestFail(const Test& test, bool failure);
    void onSuite(const Test& test, const std::string& newline);

    bool isAllPassed() const;
    void listFailures(const TestResult& result) const;

    std::string toString(const timeval& elapsed) const;
    void collectTime(const timeval& elapsed);

private:
    std::ostream& out;
    std::stack<TestInfo*> tests;

    int numOfPassed;
    int numOfFailure;
    int numOfError;
    int numOfTotalFail;

    timeval total;
};

CUT_NS_END

#endif
