#include "magellan/core/TestResult.h"
#include "magellan/core/TestCase.h"
#include "magellan/core/TestFunctor.h"
#include "magellan/core/TestListener.h"
#include "magellan/core/TestSuite.h"
#include "magellan/except/AssertionError.h"
#include "magellan/except/TestFailure.h"
#include "magellan/listener/Color.h"
#include "l0-infra/std/Algorithm.h"

MAGELLAN_NS_BEGIN

TestResult::~TestResult()
{
    stdext::clear(listeners);
    stdext::clear(failures);
}

void TestResult::add(TestListener* listener)
{
    listeners.push_back(listener);
}

#define BROADCAST(action)         \
for (auto listener : listeners) { \
    listener->action;             \
}

inline void TestResult::startTest(const Test& test)
{
    BROADCAST(startTest(test))
}

inline void TestResult::endTest(const Test& test)
{
    BROADCAST(endTest(test))
}

void TestResult::run(TestCase& test)
{
    startTest(test);
    test.runBare(*this);
    endTest(test);
}

inline void TestResult::startSuite(const Test& test)
{
    BROADCAST(startSuite(test))
}

inline void TestResult::endSuite(const Test& test)
{
    BROADCAST(endSuite(test))
}

void TestResult::run(TestSuite& test)
{
    startSuite(test);
    test.runBare(*this);
    endSuite(test);
}

inline void TestResult::startTestRun(const Test& test)
{
    BROADCAST(startTestRun(test, *this))
}


inline void TestResult::endTestRun(const Test& test)
{
    BROADCAST(endTestRun(test, *this))
}

void TestResult::runTest(Test& test)
{
    startTestRun(test);
    test.run(*this);
    endTestRun(test);
}

inline void TestResult::addFailure(TestFailure* failure)
{
    failures.push_back(failure);
    BROADCAST(addFailure(*failure))
}

inline void TestResult::reportFailure(const TestFunctor& method, Message&& msg)
{
    addFailure(new TestFailure(method, std::move(msg), true));
}

inline void TestResult::reportError(const TestFunctor& method, Message&& msg)
{
    addFailure(new TestFailure(method, std::move(msg), false));
}

bool TestResult::protect(const TestFunctor& method, const std::string& desc)
{
    try {
        return method();
    } catch (const AssertionError& e) {
        reportFailure(method, Message(std::string("assertion fail") + desc, e.what()));
    } catch (const std::exception& e) {
        reportError(method, Message(std::string("uncaught std::exception") + desc, e.what()));
    } catch (...) {
        reportError(method, Message(std::string("uncaught unknown exception") + desc));
    }

    return false;
}

namespace
{
    inline const char* titleFor(const TestFailure& failure)
    {
        return failure.isFailure() ? "[  FAILURE ] " : "[  ERROR   ] ";
    }
}

void TestResult::listFailures(std::ostream& out)
{
    if (failures.empty())
        return;

    out << RED << "[  FAILED  ] " << WHITE << failures.size() << " tests, listed below:" << std::endl;

    for (auto failure : failures)
    {
        out << RED << titleFor(*failure) << WHITE << failure->getTestName() << std::endl;
    }
}

MAGELLAN_NS_END
