#include "options/core/VariablesMap.hpp"
#include "options/core/Parsers.hpp"
#include "options/core/OptionsDescription.hpp"
#include <iostream>

OPT_NS_BEGIN

inline void VariablesMap::store(const ParsedOptions& options)
{
    for (auto& option : options.options())
    {
        if (!option.key().empty())
        {
            this->options[option.key()] = option.value();
        }
    }
}

void VariablesMap::parseArgs(int argc, const char** argv, const OptionsDescription& desc)
{
    store(CommandLineParser(argc, argv, desc).run());
}

void VariablesMap::clear()
{
    options.clear();
}

const std::string& VariablesMap::operator[](const std::string& name) const
{
    return const_cast<VariablesMap&>(*this)[name];
}

std::string& VariablesMap::operator[](const std::string& name)
{
    return options[name];
}

bool VariablesMap::has(const std::string& name) const
{
    return options.count(name) != 0;
}

void VariablesMap::dump() const
{
    for (auto& entry : options)
    {
        printf("\n=============================================================\n");
        std::cout << entry.first << "=" << entry.second << std::endl;
        printf("\n=============================================================\n");
    }
}

OPT_NS_END
