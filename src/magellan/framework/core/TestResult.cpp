#include "magellan/framework/core/TestResult.h"
#include "magellan/framework/core/TestCase.h"
#include "magellan/framework/core/TestFunctor.h"
#include "magellan/framework/core/TestListener.h"
#include "magellan/framework/core/TestSuite.h"
#include "magellan/framework/except/AssertionError.h"
#include "magellan/framework/except/TestFailure.h"
#include "magellan/infra/std/Algorithm.h"

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

inline void TestResult::startTest(const Test& test)
{
    for (auto listener : listeners)
    {
        listener->startTest(test);
    }
}

inline void TestResult::endTest(const Test& test)
{
    for (auto listener : listeners)
    {
        listener->endTest(test);
    }
}

void TestResult::run(TestCase& test)
{
    startTest(test);
    test.runBare(*this);
    endTest(test);
}

inline void TestResult::startSuite(const Test& test)
{
    for (auto listener : listeners)
    {
        listener->startSuite(test);
    }
}

inline void TestResult::endSuite(const Test& test)
{
    for (auto listener : listeners)
    {
        listener->endSuite(test);
    }
}

void TestResult::run(TestSuite& test)
{
    startSuite(test);
    test.runBare(*this);
    endSuite(test);
}

inline void TestResult::addFailure(TestFailure* failure)
{
    failures.push_back(failure);

    for (auto listener : listeners)
    {
        listener->addFailure(*failure);
    }
}

inline void TestResult::reportFailure(const Test& test, const Message& msg)
{
    addFailure(new TestFailure(test, msg, true));
}

inline void TestResult::reportError(const Test&test, const Message& msg)
{
    addFailure(new TestFailure(test, msg, false));
}

bool TestResult::protect(const Test& test, const TestFunctor& method, const std::string& desc)
{
    try {
        return method();
    } catch (const AssertionError& f) {
        reportFailure(test, Message("assertion fail", {f.what(), desc}));
    } catch (const std::exception& e) {
        reportError(test, Message("uncaught std::exception", {e.what(), desc }));
    } catch (...) {
        reportError(test, Message("uncaught unknown exception", {desc}));
    }

    return false;
}

MAGELLAN_NS_END
