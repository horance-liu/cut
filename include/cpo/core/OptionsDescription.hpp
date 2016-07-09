#ifndef OPTIONSDESCRIPTION_Fri_Apr_10_23_35_29_2015_H
#define OPTIONSDESCRIPTION_Fri_Apr_10_23_35_29_2015_H

#include <string>
#include <vector>
#include <map>
#include <memory>

#include <cpo/cpo.h>

CPO_NS_BEGIN

struct OptionDescription
{
    OptionDescription(const std::string& name,
                      const std::string& description);

    bool match(const std::string& option) const;
        
    const std::string& getKey(const std::string& option) const;
    const std::string& getLongName() const;
    const std::string& getDescription() const;
    const std::string format() const;

private:
    void setName(const std::string& name);

private:
    std::string shortName, longName, description;
};

struct OptionsDescription
{
    OptionsDescription(const std::string& caption);

    void add(std::map<std::string, std::string>&& args);

    friend std::ostream& operator<<(std::ostream& os, 
                                    const OptionsDescription& desc);
    const OptionDescription* find(const std::string& name) const;

private:
    using DescPtr = std::shared_ptr<OptionDescription>;

    std::string m_caption;
    std::vector<DescPtr> m_opt;
};

CPO_NS_END

#endif
