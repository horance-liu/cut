#include <cpo/core/OptionsDescription.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cpo/core/Parsers.hpp>
#include <cui/algo/__string__.h>

using namespace std;

CPO_NS_BEGIN

inline void OptionDescription::setName(const std::string& name)
{
    auto n = name.find(',');
    if (n != string::npos)
    {
        longName = CUI_NS::trim(name.substr(0, n));
        shortName = '-' + CUI_NS::trim(name.substr(n+1));
    }
    else
    {
        longName = CUI_NS::trim(name);
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
        m_opt.push_back(d);
    }
}

const OptionDescription* OptionsDescription::find(const std::string& name) const
{
    for(auto& one : m_opt)
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
    for (auto& var : desc.m_opt)
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
    for (auto& var : desc.m_opt)
    {
        os << "  " << left << setw(20) << var->getLongName() << setw(40) << var->getDescription() << endl;
    }
    return os;

}

CPO_NS_END

