#include "magellan/startup/TestOptions.h"
#include <iostream>

MAGELLAN_NS_BEGIN

TestOptions::TestOptions()
  : desc("Magellan")
{
    desc.add({
        {"help , h ",   "help message"},
        {"filter, f",  "set filter"},
        {"color-off,c",   "output has color or not"},
        {"format,x",     "output xml or term"},
        {"path,d", "xml out path"}
    });
}

const std::string& TestOptions::getXmlPath() const
{
    return options["path"];
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

void TestOptions::handlerHelpOption() const
{
    std::cout << desc;
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
