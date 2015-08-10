#include <magellan/listener/text/ListAllPrinter.h>
#include "magellan/core/Test.h"
#include <ostream>

MAGELLAN_NS_BEGIN

ListAllPrinter::ListAllPrinter(std::ostream& os) : os(os)
{}

void ListAllPrinter::startSuite(const Test& suite)
{
    if (suite.getName() != "All Tests")
    {
        os << suite.getName() << std::endl;
    }
}

void ListAllPrinter::startTest(const Test& test)
{
	os << "\t" << test.getName() << std::endl;
}

MAGELLAN_NS_END




