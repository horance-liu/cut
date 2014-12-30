#include <magellan/core/TestResult.h>
#include <infra/base/Collections.h>
#include <magellan/core/TestFailure.h>
#include <magellan/core/TestListener.h>
#include <magellan/core/TestCase.h>
#include <magellan/core/TestSuite.h>
#include <magellan/core/TestFunctor.h>
#include <magellan/core/AssertionError.h>
#include <infra/base/Functional.h>

MAGELLAN_NS_BEGIN

TestResult::~TestResult()
{
    clear_container(listeners);
    clear_container(failures);
    clear_container(errors);
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

    each(listeners, [&test, failure](TestListener* listener)
             { listener->addFailure(test, *failure); });
}

void TestResult::addError(Test& test, TestFailure* error)
{
    failures.push_back(error);

    each(listeners, [&test, error](TestListener* listener)
             { listener->addError(test, *error); });
}

void TestResult::startTest(Test& test)
{
    each(listeners, [&test](TestListener* listener)
             { listener->startTest(test); });
}

void TestResult::endTest(Test& test)
{
    each(listeners, [&test](TestListener* listener)
             { listener->endTest(test); });
}

void TestResult::startSuite(Test& test)
{
    each(listeners, [&test](TestListener* listener)
             { listener->startSuite(test); });
}

void TestResult::endSuite(Test& test)
{
    each(listeners, [&test](TestListener* listener)
             { listener->endSuite(test); });
}

MAGELLAN_NS_END
