#include <cut/listener/text/TextResultPrinter.h>
#include <cut/listener/util/Color.h>
#include <cut/core/Test.h>
#include <cut/core/TestResult.h>
#include <cut/except/TestFailure.h>
#include <cut/listener/util/TestInfo.h>
#include <sstream>

CUT_NS_BEGIN

TextResultPrinter::TextResultPrinter(std::ostream& out)
  : out(out), numOfPassed(0), numOfFailure(0), numOfError(0), numOfTotalFail(0)
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

inline bool TextResultPrinter::isAllPassed() const
{
    return numOfTotalFail == 0;
}

namespace
{
    inline const char* titleFor(const TestFailure& failure)
    {
        return failure.isFailure() ? "[  FAILURE ] " : "[  ERROR   ] ";
    }
}

void TextResultPrinter::listFailures(const TestResult& result) const
{
    if (isAllPassed())
        return;

    out << RED   << "[  FAILED  ] "
        << WHITE << numOfTotalFail << " tests, listed below:\n";

    result.listFailures([&](const TestFailure& failure){
        out << RED   << titleFor(failure)
            << WHITE << failure.getTestName() << std::endl;
    });
}

void TextResultPrinter::endTestRun(const Test& test, TestResult& result)
{
    out << GREEN << "[==========] "
        << WHITE << test.countTestCases() << " test cases ran." << std::endl;

    isAllPassed() ? out << GREEN : out << RED;;

    out << "[  TOTAL   ] " << WHITE
        << "PASS: "    << numOfPassed   << "  "
        << "FAILURE: " << numOfFailure  << "  "
        << "ERROR: "   << numOfError    << "  "
        << "TIME: "    << format(total) << std::endl;

    listFailures(result);
}

void TextResultPrinter::startTest(const Test& test)
{
    tests.push(new TestInfo);

    out << GREEN << "[ RUN      ] "
        << WHITE << test.getName() << std::endl;
}

inline void TextResultPrinter::onTestSucc(const Test& test)
{
    numOfPassed++;
    out << GREEN << "[       OK ] ";
}

inline void TextResultPrinter::onTestFail(const Test& test, bool failure)
{
    failure ? numOfFailure++ : numOfError++;
    numOfTotalFail++;
    out << RED   << "[  FAILED  ] ";
}

inline void TextResultPrinter::collectTime(const timeval& elapsed)
{
    total.tv_sec  += elapsed.tv_sec;
    total.tv_usec += elapsed.tv_usec;
}

inline std::string TextResultPrinter::toString(const timeval& elapsed) const
{
    return std::string("(") + format(elapsed) + ")";
}

void TextResultPrinter::endTest(const Test& test)
{
    auto lastest = tests.top();

    lastest->isSucc() ? onTestSucc(test)
                      : onTestFail(test, lastest->isFailure());

    auto elapsed = tests.top()->elapsedTime();

    out << WHITE << test.getName() << toString(elapsed) << std::endl;
    collectTime(elapsed);

    tests.pop();
}

inline void TextResultPrinter::onSuite(const Test& test, const std::string& newline)
{
    if (test.getName() == "All Tests" || test.countChildTests() == 0)
        return;

    out << GREEN << newline << "[----------] "
        << WHITE << test.countTestCases() << " tests from " << test.getName() << std::endl;
}

void TextResultPrinter::startSuite(const Test& test)
{
    tests.push(new TestInfo);
    onSuite(test, "\n");
}

void TextResultPrinter::endSuite(const Test& test)
{
    onSuite(test, "");
    tests.pop();
}

void TextResultPrinter::addFailure(const TestFailure& fail)
{
    auto test = tests.top();
    fail.isFailure() ? test->onFailure() : test->onError();

    out << fail.getExceptionMsg() << std::endl;
}

CUT_NS_END
