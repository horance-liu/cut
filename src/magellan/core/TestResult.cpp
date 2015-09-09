#include "magellan/core/TestResult.h"
#include "magellan/core/TestCase.h"
#include "magellan/core/TestFunctor.h"
#include "magellan/core/TestListener.h"
#include "magellan/core/TestSuite.h"
#include "magellan/except/AssertionError.h"
#include "magellan/except/TestFailure.h"
#include "l0-infra/std/Algorithm.h"

MAGELLAN_NS_BEGIN

TestResult::~TestResult()
{
    stdext::each(listeners, [](TestListener* p) { delete p; });
    stdext::each(failures,  [](TestFailure* p)  { delete p; });
}

void TestResult::add(TestListener* listener)
{
    listeners.push_back(listener);
}

#define BROADCAST(action) \
stdext::each(listeners, [&](TestListener* listener) { listener->action; })

void TestResult::run(TestCase& test)
{
    BROADCAST(startTest(test));
    test.runBare(*this);
    BROADCAST(endTest(test));
}

void TestResult::run(TestSuite& test)
{
    BROADCAST(startSuite(test));
    test.runBare(*this);
    BROADCAST(endSuite(test));
}

void TestResult::run(Test& test)
{
    BROADCAST(startTestRun(test, *this));
    test.run(*this);
    BROADCAST(endTestRun(test, *this));
}

inline void TestResult::addFailure(TestFailure* failure)
{
    failures.push_back(failure);
    BROADCAST(addFailure(*failure));
}

inline void TestResult::reportFailure(const TestFunctor& method, Message&& msg)
{
    addFailure(new TestFailure(method, std::move(msg), true));
}

inline void TestResult::reportError(const TestFunctor& method, Message&& msg)
{
    addFailure(new TestFailure(method, std::move(msg), false));
}

bool TestResult::protect(const TestFunctor& functor, const std::string& desc)
{
    try {
        return functor();
    } catch (const AssertionError& e) {
        reportFailure(functor, Message(std::string("assertion fail") + desc, e.what()));
    } catch (const std::exception& e) {
        reportError(functor, Message(std::string("uncaught std::exception") + desc, e.what()));
    } catch (...) {
        reportError(functor, Message(std::string("uncaught unknown exception") + desc));
    }

    return false;
}

bool TestResult::isSucc() const
{
    return failures.empty();
}

MAGELLAN_NS_END
