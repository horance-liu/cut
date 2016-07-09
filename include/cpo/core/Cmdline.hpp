#ifndef CMDLINE_Sun_Apr_19_00_17_15_2015_H
#define CMDLINE_Sun_Apr_19_00_17_15_2015_H

#include <cpo/core/OptionsDescription.hpp>

CPO_NS_BEGIN

struct Option;

struct Cmdline
{
    Cmdline(const std::vector<std::string>& args);
    Cmdline(int argc, const char** argv);

    void setDescription(const OptionsDescription& desc);
    std::vector<Option> run();

private:
    void init(const std::vector<std::string>& args);
    std::vector<Option> parseLongOption(const std::string& arg);
    std::vector<Option> parseShortOption(const std::string& arg);
    void doAllParser(const std::string& arg, std::vector<Option>& result);

private:
    std::vector<std::string> args;
    const OptionsDescription* desc;
};

CPO_NS_END

#endif

