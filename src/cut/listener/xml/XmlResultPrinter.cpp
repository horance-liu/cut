#include <cut/listener/xml/XmlResultPrinter.h>
#include <cut/listener/util/TestInfo.h>
#include <cut/listener/util/XmlBuilder.h>
#include <cut/except/TestFailure.h>
#include <cut/core/Test.h>
#include <cut/hook/runtime/Runtime.h>
#include <iostream>
#include <fstream>
#include <iosfwd>


CUT_NS_BEGIN

struct XmlResultPrinter::Statistics
{
    Statistics()
    {
        reset();
    }

    void reset()
    {
        numOfPassed = 0;
        numOfFailure = 0;
        numOfError = 0;
        totalTime.tv_sec = 0;
        totalTime.tv_usec = 0;
    }

    void onTestSucc()
    {
        numOfPassed++;
    }

    void onTestFailure()
    {
        numOfFailure++;
    }

    void onTestError()
    {
        numOfError++;
    }

    void collectTime(const timeval& elapsed)
    {
        totalTime.tv_sec  += elapsed.tv_sec;
        totalTime.tv_usec += elapsed.tv_usec;
    }

    timeval totalElapsedTime() const
    {
        return totalTime;
    }

public:
    int numOfPassed;
    int numOfFailure;
    int numOfError;
    timeval totalTime;
};

////////////////////////////////////////////////////////////////////////////////////////
XmlResultPrinter::XmlResultPrinter()
    : node("testsuites")
    , builder(new XmlBuilder(&node))
    , testStat(new Statistics())
    , suiteStat(new Statistics())
{
}

XmlResultPrinter::~XmlResultPrinter()
{
    delete builder;
    delete testStat;
    delete suiteStat;

    while (!tests.empty())
    {
        auto top = tests.top();
        tests.pop();
        delete top;
    }
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

void XmlResultPrinter::startTestRun(const Test& test, TestResult&)
{
    builder->addAttribute("tests", test.countTestCases());
}

void XmlResultPrinter::endTestRun(const Test&, TestResult&)
{
    addStatusAndTimeAttribute("testsuites", *testStat);

    builder->addAttributeTo("testsuites", "name", "AllTests");

    clearStatsBy(*testStat);
    toXml();

}

void XmlResultPrinter::startSuite(const Test& test)
{
    if (isAllTestSuiteBy(test.getName())) return;

    builder->addToParent("testsuites", "testsuite");

    builder->addAttribute("name", test.getName());
    builder->addAttribute("test", test.countTestCases());
}

void XmlResultPrinter::endSuite(const Test& test)
{
    if (isAllTestSuiteBy(test.getName())) return;

    addStatusAndTimeAttribute("testsuite", *suiteStat);

    clearStatsBy(*suiteStat);
}

void XmlResultPrinter::startTest(const Test& test)
{
    recordStartTime();

    builder->addToParent("testsuite", "testcase");
    builder->addAttribute("name", test.getName());
}

namespace
{
    const std::string getShortTestcaseName(const std::string& name)
    {
        return name.substr(0, name.find("::"));
    }

    const std::string getExpectedMsg(const std::string& msg)
    {
        return msg.substr(msg.find("Expected:"), msg.find("but:"));
    }

    const std::string getExceptionMsg(const std::string& msg)
    {
        return msg.substr(msg.find("but:"), msg.find("got false"));
    }
}

void XmlResultPrinter::endTest(const Test& test)
{
    auto lastest = tests.top();

    auto elapsedTime = lastest->elapsedTime();
    collectTime(elapsedTime);

    std::string result = handlerTestResult(*lastest);

    builder->addAttributeTo("testcase", "status",    result);
    builder->addAttributeTo("testcase", "time",      format(elapsedTime));
    builder->addAttributeTo("testcase", "classname", getShortTestcaseName(test.getName()));

    tests.pop();
}

void XmlResultPrinter::collectTime(const timeval& elapsed)
{
    testStat->totalTime.tv_sec  += elapsed.tv_sec;
    testStat->totalTime.tv_usec += elapsed.tv_usec;

    suiteStat->totalTime.tv_sec  += elapsed.tv_sec;
    suiteStat->totalTime.tv_usec += elapsed.tv_usec;
}

void XmlResultPrinter::addFailure(const TestFailure& fail)
{
    auto test = tests.top();
    fail.isFailure() ? test->onFailure() : test->onError();

    builder->addChild("failure");
    builder->addAttribute("message", getExpectedMsg(fail.getExceptionMsg()));

    builder->addSibling("failure");
    builder->addAttribute("message", getExceptionMsg(fail.getExceptionMsg()));
}

namespace
{
    void writeXmlFile(const std::string& s)
    {
        std::fstream file;

        file.open("result.xml", std::ios::out);

        if (file)
        {
            file << s;
        }

        file.close();
    }
}


void XmlResultPrinter::toXml() const
{
    std::string result = "<?xml version=\"1.0\" encoding='utf-8'  standalone='yes' ?>\n";

    result += node.toXml();
    writeXmlFile(result);
}

void XmlResultPrinter::recordStartTime()
{
    tests.push(new TestInfo);
}

void XmlResultPrinter::addStatusAndTimeAttribute(const std::string& name, const Statistics& stats)
{
    builder->addAttributeTo(name, "failures", stats.numOfFailure);
    builder->addAttributeTo(name, "errors",   stats.numOfError);
    builder->addAttributeTo(name, "time",     format(stats.totalTime));
}

void XmlResultPrinter::clearStatsBy(Statistics& name)
{
    name.reset();
}

bool XmlResultPrinter::isAllTestSuiteBy(const std::string& name) const
{
    return name == "All Tests";
}

const char* XmlResultPrinter::handlerTestResult(const TestInfo& info)
{
    if (info.isSucc())
    {
        testStat->onTestSucc();
        suiteStat->onTestSucc();

        return "successful";
    }
    else if (info.isFailure())
    {
        testStat->onTestFailure();
        suiteStat->onTestFailure();

        return "failure";
    }
    else
    {
        testStat->onTestError();
        suiteStat->onTestError();

        return "error";
    }
}

CUT_NS_END
