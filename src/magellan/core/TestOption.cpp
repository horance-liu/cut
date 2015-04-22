#include <magellan/core/TestOption.h>
#include <iostream>

MAGELLAN_NS_BEGIN

TestOption& TestOption::getInstance()
{
    static TestOption testOption;

    return testOption;
}

void TestOption::capatureOptionsFrom(int argc, const char** argv)
{
    options.parseArgs(argc, argv, desc);
}

bool TestOption::hasHelpOption() const
{
    return options.has("help");
}

// TO do : waiting call infra/options print function
void TestOption::handlerHelpOption() const
{
    const std::string SEPARATOR = "          ";

    std::cout << "\tMagellan Options Help\n"
              << "==============================\n"
              << "Option Name" << SEPARATOR <<"Option Description" << std::endl;
    std::cout << "==============================\n"
              << "help(--help, -h) :" << SEPARATOR << "Help message" << std::endl
              << "filter(--filter) :" << SEPARATOR << "set filter" << std::endl;
}

bool TestOption::handlerFilterOptionBy(const std::string& name) const
{
    return (!hasFilterOption())
        || (hasFilterOption() && isMatchedName(name));
}

bool TestOption::hasFilterOption() const
{
    return options.has("filter");
}

bool TestOption::isMatchedName(const std::string& name) const
{
    return name == options["filter"];  //To do: need fixed to support *
}

TestOption::TestOption()
    : desc("Magellan Options")
    , options(VariablesMap::getInstance())
{
    desc.add({
        {"help",   "help message"},
        {"filter", "set filter"},
    });
}

MAGELLAN_NS_END
