#include "magellan/startup/TestOptions.h"
#include <l0-infra/std/String.h>
#include <stdlib.h>
#include <iostream>
#include <regex>

MAGELLAN_NS_BEGIN

TestOptions::TestOptions() : desc("magellan")
{
    desc.add({
        {"help,     h",   "help message"},
        {"filter,   f",   "--filter=pattern"},
        {"color,    c",   "--color=[yes|no]"},
        {"xml,      x",   "print test result into XML file"},
		{"list,     l",   "list all tests without running them"},
        {"progress, p",   "print test result in progress bar"},
        {"verbose,  v",   "verbosely list tests processed"},
        {"repeat,   r",   "how many times to repeat each test"}
    });

    options["color"]  = "yes";
    options["repeat"] = "1";
}

void TestOptions::clear()
{
	options.clear();
}

int TestOptions::repeat() const
{
	return options.has("list") ? 1 : stdext::string_as<int>(options["repeat"]);
}

bool TestOptions::verbose() const
{
	return options.has("verbose");
}

bool TestOptions::list() const
{
	return options.has("list");
}

bool TestOptions::progress() const
{
    return options.has("progress");
}

void TestOptions::parse(int argc, const char** argv)
{
    options.parseArgs(argc, argv, desc);
}

const OPTIONS_NS::OptionsDescription& TestOptions::description() const
{
    return desc;
}

bool TestOptions::xml() const
{
    return options.has("xml");
}

bool TestOptions::colorful() const
{
    return options.has("color") && options["color"] == "yes";
}

bool TestOptions::help() const
{
    return options.has("help");
}

inline bool TestOptions::matches(const std::string& name) const
{
    const std::regex pattern(options["filter"]);
    return std::regex_match(name, pattern);
}

bool TestOptions::filter(const std::string& name) const
{
    return !options.has("filter") || matches(name);
}

MAGELLAN_NS_END
