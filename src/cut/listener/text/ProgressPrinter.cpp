#include <cut/listener/text/ProgressPrinter.h>

CUT_NS_BEGIN

ProgressPrinter::ProgressPrinter(std::ostream&)
{
}

void ProgressPrinter::startTest(const Test&)
{
  // TODO
}

void ProgressPrinter::endTestRun(const Test& test, TestResult& result)
{
  // TODO
}

void ProgressPrinter::addFailure(const TestFailure&)
{
  // TODO
}

CUT_NS_END
