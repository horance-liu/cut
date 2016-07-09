#ifndef INCLUDE_cut_LISTENER_TEXT_LISTALLTESTPRINTER_H_
#define INCLUDE_cut_LISTENER_TEXT_LISTALLTESTPRINTER_H_

#include <cut/core/TestListener.h>
#include <iostream>

CUT_NS_BEGIN

struct ListAllPrinter : TestListener
{
	ListAllPrinter(std::ostream& = std::cout);

private:
    __OVERRIDE__(void startSuite(const Test&));
	__OVERRIDE__(void startTest(const Test&));

private:
    std::ostream& os;
};

CUT_NS_END

#endif
