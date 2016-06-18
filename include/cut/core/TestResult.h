#ifndef _7Q5LD8WDHIYD4YAN2MCI6W2EECFPWRMQK7TPIRTA7HRM7L83N1O5MX0               
#define _7Q5LD8WDHIYD4YAN2MCI6W2EECFPWRMQK7TPIRTA7HRM7L83N1O5MX0

#include <cut/cut.h>
#include <vector>
#include <string>

CUT_NS_BEGIN

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
    void run(Test&);

    bool isSucc() const;
    bool protect(const TestFunctor&, const std::string&);

    template <typename Functor>
    void listFailures(Functor functor) const
    {
        for (auto failure : failures)
        {
            functor(*failure);
        }
    }

private:
    void addFailure(TestFailure*);
    void addError(TestFailure*);

    void reportFailure(const TestFunctor& method, Message&&);
    void reportError(const TestFunctor& method, Message&&);

private:
    std::vector<TestListener*> listeners;
    std::vector<TestFailure*>  failures;
};

CUT_NS_END

#endif
