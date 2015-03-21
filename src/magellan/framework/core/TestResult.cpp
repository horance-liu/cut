#include "magellan/framework/core/TestResult.h"
#include "magellan/framework/core/AssertionError.h"
#include "magellan/framework/core/TestCase.h"
#include "magellan/framework/core/TestFailure.h"
#include "magellan/framework/core/TestFunctor.h"
#include "magellan/framework/core/TestListener.h"
#include "magellan/framework/core/TestSuite.h"
#include "magellan/infra/std/Algorithm.h"

MAGELLAN_NS_BEGIN

TestResult::~TestResult()
{
    stdext::clear(listeners);
    stdext::clear(failures);
    stdext::clear(errors);
}

void TestResult::reportFailure(Test& test, const Message& msg)
{
    addFailure(test, new TestFailure(test, msg, false));
}

void TestResult::reportError(Test&test, const Message& msg)
{
    addError(test, new TestFailure(test, msg, true));
}

bool TestResult::protect(Test& test, const TestFunctor& method, const std::string& desc)
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

void TestResult::run(TestCase& test)
{
    startTest(test);
    test.runBare(*this);
    endTest(test);
}

void TestResult::run(TestSuite& test)
{
    startSuite(test);
    test.runBare(*this);
    endSuite(test);
}

void TestResult::add(TestListener* listener)
{
    listeners.push_back(listener);
}

void TestResult::addFailure(Test& test, TestFailure* failure)
{
    failures.push_back(failure);

    for (auto listener : listeners)
    {
        listener->addFailure(test, *failure);
    }
}

void TestResult::addError(Test& test, TestFailure* error)
{
    failures.push_back(error);

    for (auto listener : listeners)
    {
        listener->addError(test, *error);
    }
}

void TestResult::startTest(Test& test)
{
    for (auto listener : listeners)
    {
        listener->startTest(test);
    }
}

void TestResult::endTest(Test& test)
{
    for (auto listener : listeners)
    {
        listener->endTest(test);
    }
}

void TestResult::startSuite(Test& test)
{
    for (auto listener : listeners)
    {
        listener->startSuite(test);
    }
}

void TestResult::endSuite(Test& test)
{
    for (auto listener : listeners)
    {
        listener->endSuite(test);
    }
}

MAGELLAN_NS_END
