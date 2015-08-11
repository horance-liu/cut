#include "magellan/listener/text/ProgressPrinter.h"

MAGELLAN_NS_BEGIN

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

MAGELLAN_NS_END
