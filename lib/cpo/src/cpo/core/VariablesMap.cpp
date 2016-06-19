#include <cpo/core/VariablesMap.hpp>

#include <iostream>

#include <cpo/core/OptionsDescription.hpp>
#include <cpo/core/Parsers.hpp>

CPO_NS_BEGIN

inline void VariablesMap::store(const ParsedOptions& opt)
{
    for (auto& option : opt.options())
    {
        if (!option.key().empty())
        {
            this->opt[option.key()] = option.value();
        }
    }
}

void VariablesMap::parseArgs(int argc, const char** argv, const OptionsDescription& desc)
{
    store(CommandLineParser(argc, argv, desc).run());
}

void VariablesMap::clear()
{
    opt.clear();
}

const std::string& VariablesMap::operator[](const std::string& name) const
{
    return const_cast<VariablesMap&>(*this)[name];
}

std::string& VariablesMap::operator[](const std::string& name)
{
    return opt[name];
}

bool VariablesMap::has(const std::string& name) const
{
    return opt.count(name) != 0;
}

void VariablesMap::dump() const
{
    for (auto& entry : opt)
    {
        printf("\n=============================================================\n");
        std::cout << entry.first << "=" << entry.second << std::endl;
        printf("\n=============================================================\n");
    }
}

CPO_NS_END
