#include "magellan/startup/TestOptions.h"
#include <l0-infra/std/String.h>
#include <stdlib.h>
#include <iostream>
#include <regex>

MAGELLAN_NS_BEGIN
using namespace std;

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

void TestOptions::clear()
{
	options.clear();
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

void TestOptions::parse(int argc, const char** argv)
{
    options.parseArgs(argc, argv, desc);
    if(options.has("help")) cout << desc;
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

bool TestOptions::doFilter(const std::string& name) const
{
    if (!options.has("filter")) return false;
    return isMatchedName(name);
}

bool TestOptions::isMatchedName(const std::string& name) const
{
	const regex pattern(options["filter"]);
	return regex_match(name, pattern);
}

MAGELLAN_NS_END
