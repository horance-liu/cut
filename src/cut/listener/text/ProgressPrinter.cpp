#include <cut/listener/text/ProgressPrinter.h>

CUT_NS_BEGIN

ProgressPrinter::ProgressPrinter(std::ostream& out) : out(out)
{}

void ProgressPrinter::startTest(const Test&)
{
}

void ProgressPrinter::endTestRun(const Test& test, TestResult& result)
{
}

void ProgressPrinter::addFailure(const TestFailure&)
{
}

CUT_NS_END
