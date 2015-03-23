#ifndef _7Q5LD8WDHIYD4YAN2MCI6W2EECFPWRMQK7TPIRTA7HRM7L83N1O5MX0               
#define _7Q5LD8WDHIYD4YAN2MCI6W2EECFPWRMQK7TPIRTA7HRM7L83N1O5MX0

#include <magellan/framework/magellan.h>
#include <vector>
#include <string>
#include <ostream>

MAGELLAN_NS_BEGIN

struct Test;
struct TestCase;
struct TestSuite;
struct TestFailure;
struct TestListener;
struct TestFunctor;
struct Message;

struct TestResult
{
    ~TestResult();

    void add(TestListener*);
    
    void run(TestCase&);
    void run(TestSuite&);
    void runTest(Test& test);
    void listFailures(std::ostream& out);

    bool protect(const TestFunctor&, const std::string&);

private:
    void startTestRun(const Test& test);
    void endTestRun(const Test& test);

    void startTest(const Test&);
    void endTest(const Test&);

    void startSuite(const Test&);
    void endSuite(const Test&);

    void addFailure(TestFailure*);
    void addError(TestFailure*);

    void reportFailure(const TestFunctor& method, const Message&);
    void reportError(const TestFunctor& method, const Message&);

private:
    std::vector<TestListener*> listeners;
    std::vector<TestFailure*>  failures;
};

MAGELLAN_NS_END

#endif
