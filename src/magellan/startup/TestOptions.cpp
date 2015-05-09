#include "magellan/startup/TestOptions.h"
#include <l0-infra/std/String.h>
#include <stdlib.h>
#include <iostream>

MAGELLAN_NS_BEGIN

TestOptions::TestOptions()
  : desc("Magellan")
{
    desc.add({
        {"help , h ",   "help message"},
        {"filter, f",  "set filter = string"},
        {"color-off,c",   "output has color or not"},
        {"format,x",     "output xml or term"},
		{"list, l",      "list all test not run"},
        {"verbose",      "print debug info in running"},
        {"sandbox",      "support test run in sandbox"},
        {"repeat, r",    "repeat all test with <value> times"}
    });
}

bool TestOptions::sandbox() const
{
	return options.has("sandbox");
}

unsigned int TestOptions::repeat() const
{
	if(!options.has("repeat") || options.has("list")) return 1;

	return stdext::string_as<unsigned int>(options["repeat"]);
}

bool TestOptions::verbose() const
{
	return options.has("verbose");
}

bool TestOptions::listAllTest() const
{
	return options.has("list");
}

void TestOptions::capatureOptionsFrom(int argc, const char** argv)
{
    options.parseArgs(argc, argv, desc);
}

bool TestOptions::outPutXml() const
{
    return options.has("format") && options["format"] == "xml";
}

bool TestOptions::colorOn() const
{
    return !options.has("color-off");
}

bool TestOptions::hasHelpOption() const
{
    return options.has("help");
}

int TestOptions::handlerHelpOption() const
{
    std::cout << desc;
    return EXIT_SUCCESS;
}

bool TestOptions::handlerFilterOptionBy(const std::string& name) const
{
    return (!hasFilterOption())
            || (hasFilterOption() && isMatchedName(name));
}

bool TestOptions::hasFilterOption() const
{
    return options.has("filter");
}

bool TestOptions::isMatchedName(const std::string& name) const
{
    return name == options["filter"];  //To do: need fixed to support *
}

MAGELLAN_NS_END
