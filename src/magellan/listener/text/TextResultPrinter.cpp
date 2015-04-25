#include "magellan/listener/text/TextResultPrinter.h"
#include "magellan/listener/util/Color.h"
#include "magellan/core/Test.h"
#include "magellan/core/TestResult.h"
#include "magellan/except/TestFailure.h"
#include "magellan/listener/util/TestInfo.h"
#include <iosfwd>
#include <sstream>


MAGELLAN_NS_BEGIN

TextResultPrinter::TextResultPrinter(std::ostream& out)
  : out(out)
  , numOfPassed(0)
  , numOfFailure(0)
  , numOfError(0)
{
    total.tv_sec  = 0;
    total.tv_usec = 0;
}

TextResultPrinter::~TextResultPrinter()
{
    while (!tests.empty())
    {
        auto top = tests.top();
        tests.pop();
        delete top;
    }
}

void TextResultPrinter::startTestRun(const Test& test, TestResult&)
{
    out << GREEN << "[==========] "
        << WHITE << "Running " << test.countTestCases() << " test cases." << std::endl;
}

void TextResultPrinter::totalColor() const
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

        ss << elapsed.tv_usec << " us";

        return ss.str();
    }
}

void TextResultPrinter::endTestRun(const Test& test, TestResult& result)
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

void TextResultPrinter::startTest(const Test& test)
{
    tests.push(new TestInfo);

    out << GREEN << "[ RUN      ] "
        << WHITE << test.getName() << std::endl;
}

void TextResultPrinter::onTestSucc(const Test& test)
{
    numOfPassed++;
    out << GREEN << "[       OK ] ";
}

void TextResultPrinter::onTestFail(const Test& test, const bool failure)
{
    failure ? numOfFailure++ : numOfError++;
    out << RED   << "[  FAILED  ] ";
}

void TextResultPrinter::collectTime(const timeval& elapsed)
{
    total.tv_sec  += elapsed.tv_sec;
    total.tv_usec += elapsed.tv_usec;
}

std::string TextResultPrinter::elapsedTimeAsString(const timeval& elapsed) const
{
    return std::string("(") + format(elapsed) + ")";
}


void TextResultPrinter::endTest(const Test& test)
{
    auto lastest = tests.top();

    lastest->isSucc() ? onTestSucc(test)
                      : onTestFail(test, lastest->isFailure());

    auto elapsed = tests.top()->elapsedTime();

    out << WHITE << test.getName() << elapsedTimeAsString(elapsed) << std::endl;
    collectTime(elapsed);

    tests.pop();
}

inline void TextResultPrinter::onSuite(const Test& test)
{
    out << GREEN << "[----------] "
        << WHITE << test.countTestCases() << " tests from " << test.getName();

    out << std::endl;

}

void TextResultPrinter::startSuite(const Test& test)
{
    tests.push(new TestInfo);
    onSuite(test);
}

void TextResultPrinter::endSuite(const Test& test)
{
    onSuite(test);
    out << std::endl;
    tests.pop();
}

void TextResultPrinter::addFailure(const TestFailure& fail)
{
    auto test = tests.top();
    fail.isFailure() ? test->onFailure() : test->onError();

    out << fail.getExceptionMsg() << std::endl;
}

MAGELLAN_NS_END
