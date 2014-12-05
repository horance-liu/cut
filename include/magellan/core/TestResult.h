#ifndef _7Q5LD8WDHIYD4YAN2MCI6W2EECFPWRMQK7TPIRTA7HRM7L83N1O5MX0               
#define _7Q5LD8WDHIYD4YAN2MCI6W2EECFPWRMQK7TPIRTA7HRM7L83N1O5MX0

#include <magellan/base/magellan.h>
#include <vector>
#include <string>

MAGELLAN_NS_BEGIN

struct Test;
struct TestCase;
struct TestSuite;
struct TestFailure;
struct TestListener;
struct TestMethod;
struct Message;

struct TestResult
{
    ~TestResult();

    void run(TestCase&);
    void run(TestSuite&);

    bool protect(Test& test, const TestMethod&, const std::string&);

    void add(TestListener*);

private:
    void startTest(Test&);
    void endTest(Test&);

    void startSuite(Test&);
    void endSuite(Test&);

    void addFailure(Test&, TestFailure*);
    void addError(Test&, TestFailure*);

    void reportFailure(Test& test, const Message&);
    void reportError(Test&test, const Message&);

private:
    std::vector<TestListener*> listeners;
    std::vector<TestFailure*>  failures;
    std::vector<TestFailure*>  errors;
};

MAGELLAN_NS_END

#endif
