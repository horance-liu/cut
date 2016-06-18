#include "options/core/OptionsDescription.hpp"
#include "options/core/Parsers.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cub/algo/String.h>

using namespace std;

OPT_NS_BEGIN

inline void OptionDescription::setName(const std::string& name)
{
    auto n = name.find(',');
    if (n != string::npos)
    {
        longName = CUB_NS::trim(name.substr(0, n));
        shortName = '-' + CUB_NS::trim(name.substr(n+1));
    }
    else
    {
        longName = CUB_NS::trim(name);
    }
}

OptionDescription::OptionDescription
    ( const std::string& name
    , const std::string& description)
    : description(description)
{
    setName(name);
}

bool OptionDescription::match(const std::string& option) const
{
    return option == longName || option == shortName;
}

const std::string& OptionDescription::getKey(const std::string& option) const
{        
    return longName.empty() ? shortName : longName;
}

const std::string& OptionDescription::getLongName() const
{
    return longName;
}

const std::string OptionDescription::format() const
{
    return "[--" + longName + "|" + shortName +"]";
}

const std::string& OptionDescription::getDescription() const
{
    return description;
}

OptionsDescription::OptionsDescription(const std::string& caption)
    : m_caption(caption)
{
}
    
void OptionsDescription::add(std::map<std::string, std::string>&& args)
{
    for (auto& entry : args)
    {
        DescPtr d(new OptionDescription(entry.first, entry.second));
        m_options.push_back(d);
    }
}

const OptionDescription* OptionsDescription::find(const std::string& name) const
{
    for(auto& one : m_options)
    {
        if(one->match(name)) return one.get();
    }
    return 0;
}

using namespace std;

ostream& operator<<(ostream& os, const OptionsDescription& desc)
{
    const string usage("usage: ");
    os << setfill('=') << setw(80) << "" << endl << setfill(' ');

    os<< usage << desc.m_caption <<" ";

    int i = 1;
    for (auto& var : desc.m_options)
    {
        os << var->format() << " ";
        if((i++)% 4 == 0 )
        {
            os << endl;
            os << setw(desc.m_caption.size() + usage.size()) <<"";
        }
    }
    os<<endl;
    os<<setfill('=') << setw(80) << "" << endl << setfill(' ');
    for (auto& var : desc.m_options)
    {
        os << "  " << left << setw(20) << var->getLongName() << setw(40) << var->getDescription() << endl;
    }
    return os;

}

OPT_NS_END

