#include <cpo/core/VariablesMap.hpp>
#include <cpo/core/Parsers.hpp>
#include <cpo/core/OptionsDescription.hpp>
#include <iostream>

CPO_NS_BEGIN

inline void VariablesMap::store(const ParsedOptions& options)
{
    for (auto& opt : options.options())
    {
        if (!opt.key().empty())
        {
            this->opt[opt.key()] = opt.value();
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
