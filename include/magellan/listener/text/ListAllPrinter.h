#ifndef INCLUDE_MAGELLAN_LISTENER_TEXT_LISTALLTESTPRINTER_H_
#define INCLUDE_MAGELLAN_LISTENER_TEXT_LISTALLTESTPRINTER_H_

#include "magellan/core/TestListener.h"
#include <iostream>

MAGELLAN_NS_BEGIN

struct ListAllPrinter : TestListener
{
	ListAllPrinter(std::ostream& = std::cout);

private:
    OVERRIDE(void startSuite(const Test&));
	OVERRIDE(void startTest(const Test&));

private:
    std::ostream& os;
};

MAGELLAN_NS_END

#endif
