#ifndef HC1529C5B_742D_4014_BBBF_7533B3E13905
#define HC1529C5B_742D_4014_BBBF_7533B3E13905

#include "magellan/core/TestListener.h"
#include <iostream>
#include <stack>
#include <time.h>

MAGELLAN_NS_BEGIN

struct TestInfo;

struct TextResultPrinter : TestListener
{
    TextResultPrinter(std::ostream& = std::cout);
    ~TextResultPrinter();

private:
    OVERRIDE(void startTestRun(const Test&, TestResult&));
    OVERRIDE(void endTestRun(const Test&, TestResult&));

    OVERRIDE(void startSuite(const Test&));
    OVERRIDE(void endSuite(const Test&));

    OVERRIDE(void startTest(const Test&));
    OVERRIDE(void endTest(const Test&));

    OVERRIDE(void addFailure(const TestFailure&));

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

MAGELLAN_NS_END

#endif
