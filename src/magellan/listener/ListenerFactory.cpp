#include "magellan/listener/ListenerFactory.h"
#include "magellan/core/TestResult.h"
#include "magellan/listener/text/TextResultPrinter.h"

#include <iostream>

MAGELLAN_NS_BEGIN

void ListenerFactory::create(TestResult& results)
{
    results.add(new TextResultPrinter(std::cout));
}

MAGELLAN_NS_END
