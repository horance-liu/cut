#include "magellan/listener/ResultPrinter.h"
#include "magellan/listener/Color.h"
#include "magellan/core/Test.h"
#include "magellan/core/TestResult.h"
#include "magellan/except/TestFailure.h"
#include <memory>
#include <sstream>

MAGELLAN_NS_BEGIN

struct ResultPrinter::TestInfo
{
    TestInfo()
      : timer(std::make_unique<Timer>())
      , succ(true)
      , failure(false)
      , error(false)
    {}

    void onFailure()
    {
        succ = false;
        failure = true;
    }

    void onError()
    {
        succ = false;
        error = true;
    }

    bool isSucc() const
    {
        return succ;
    }

    bool isFailure() const
    {
        return !succ && failure;
    }

    bool isError() const
    {
        return !succ && error;
    }

    timeval elapsedTime()
    {
        return timer->getElapsedTime();
    }

private:
    bool succ;
    bool failure;
    bool error;
    std::unique_ptr<Timer> timer;
};

ResultPrinter::ResultPrinter(std::ostream& out)
  : out(out)
  , numOfPassed(0)
  , numOfFailure(0)
  , numOfError(0)
{
    total.tv_sec  = 0;
    total.tv_usec = 0;
}

ResultPrinter::~ResultPrinter()
{
    while (!tests.empty())
    {
        auto top = tests.top();
        tests.pop();
        delete top;
    }
}

void ResultPrinter::startTestRun(const Test& test, TestResult&)
{
    out << GREEN << "[==========] "
        << WHITE << "Running " << test.countTestCases() << " test cases." << std::endl;
}

void ResultPrinter::totalColor() const
{
    (numOfFailure == 0 && numOfError == 0) ? out << GREEN : out << RED;
}

namespace
{
    std::string format(const timeval& elapsed)
    {
        std::stringstream ss;

        if (elapsed.tv_sec > 0)
            ss << elapsed.tv_sec << " s ";

        ss << elapsed.tv_usec << " ms";

        return ss.str();
    }
}

void ResultPrinter::endTestRun(const Test& test, TestResult& result)
{
    out << GREEN << "[==========] "
        << WHITE << test.countTestCases() << " test cases ran." << std::endl;

    totalColor();

    out << "[  TOTAL   ] " << WHITE
            << "PASS: "    << numOfPassed  << "  "
            << "FAILURE: " << numOfFailure << "  "
            << "ERROR: "   << numOfError   << "  "
            << "TIME: "    << format(total)
            << std::endl;

    result.listFailures(out);
}

void ResultPrinter::startTest(const Test& test)
{
    tests.push(new TestInfo);

    out << GREEN << "[ RUN      ] "
        << WHITE << test.getName() << std::endl;
}

void ResultPrinter::onTestSucc(const Test& test)
{
    numOfPassed++;
    out << GREEN << "[       OK ] ";
}

void ResultPrinter::onTestFail(const Test& test, const bool failure)
{
    failure ? numOfFailure++ : numOfError++;
    out << RED   << "[  FAILED  ] ";
}

void ResultPrinter::collectTime(const timeval& elapsed)
{
    total.tv_sec  += elapsed.tv_sec;
    total.tv_usec += elapsed.tv_usec;
}

std::string ResultPrinter::elapsedTimeAsString(const timeval& elapsed) const
{
    return std::string("(") + format(elapsed) + ")";
}

void ResultPrinter::endTest(const Test& test)
{
    auto lastest = tests.top();

    lastest->isSucc() ? onTestSucc(test)
                      : onTestFail(test, lastest->isFailure());

    auto elapsed = tests.top()->elapsedTime();

    out << WHITE << test.getName() << elapsedTimeAsString(elapsed) << std::endl;
    collectTime(elapsed);

    tests.pop();
}

inline void ResultPrinter::onSuite(const Test& test)
{
    out << GREEN << "[----------] "
        << WHITE << test.countTestCases() << " tests from " << test.getName();

    out << std::endl;

}

void ResultPrinter::startSuite(const Test& test)
{
    tests.push(new TestInfo);
    onSuite(test);
}

void ResultPrinter::endSuite(const Test& test)
{
    onSuite(test);
    out << std::endl;
    tests.pop();
}

void ResultPrinter::addFailure(const TestFailure& fail)
{
    auto test = tests.top();
    fail.isFailure() ? test->onFailure() : test->onError();

    out << fail.getExceptionMsg() << std::endl;
}

MAGELLAN_NS_END
