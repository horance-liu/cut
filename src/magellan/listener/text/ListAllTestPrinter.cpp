#include "magellan/listener/text/ListAllTestPrinter.h"
#include "magellan/core/Test.h"
#include "magellan/listener/util/Color.h"

MAGELLAN_NS_BEGIN

ListAllTestPrinter::ListAllTestPrinter(std::ostream& os):os(os)
{

}

void ListAllTestPrinter::startTestRun(const Test& test, TestResult&)
{
	os << GREEN << "total has " << test.countTestCases() << " test cases." << std::endl;
}

void ListAllTestPrinter::startSuite(const Test& suite)
{
	os<< std::endl<< YELLOW <<suite.getName()<<" has "<< suite.countChildTests()
			<<" test" <<std::endl;
}

void ListAllTestPrinter::startTest(const Test& test)
{
	os<<WHITE<<test.getName()<<std::endl;
}

MAGELLAN_NS_END




