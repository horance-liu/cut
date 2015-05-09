#include "magellan/listener/ListenerFactory.h"
#include "magellan/core/TestResult.h"
#include "magellan/listener/text/TextResultPrinter.h"
#include "magellan/startup/TestOptions.h"
#include "magellan/hook/runtime/Runtime.h"
#include "magellan/listener/xml/XmlResultPrinter.h"
#include "magellan/listener/text/ListAllTestPrinter.h"
#include <iostream>

MAGELLAN_NS_BEGIN

void ListenerFactory::create(TestResult& results)
{
	RUNTIME(TestOptions, options);

	if(options.listAllTest())
	{
		results.add(new ListAllTestPrinter(std::cout));
	}
	else
	{
		results.add(new TextResultPrinter(std::cout));
		if(options.outPutXml()) results.add(new XmlResultPrinter());
	}
}

MAGELLAN_NS_END
