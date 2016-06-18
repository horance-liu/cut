#ifndef PARSERS_Thu_Apr_16_23_57_14_2015_H
#define PARSERS_Thu_Apr_16_23_57_14_2015_H

#include <opt/core/OptionsDescription.hpp>
#include <opt/core/Option.hpp>
#include <cub/dci/Role.h>
#include <opt/core/Cmdline.hpp>

OPT_NS_BEGIN

struct OptionsDescription;

DEFINE_ROLE(ParsedOptions)
{
    ABSTRACT(const std::vector<Option>& opt() const);
    ABSTRACT(const OptionsDescription& description() const);
};

struct CommandLineParser : private Cmdline, ParsedOptions{

    CommandLineParser( int argc, const char** argv
                     , const OptionsDescription& desc);

    const ParsedOptions& run();

private:
    OVERRIDE(const std::vector<Option>& opt() const);
    OVERRIDE(const OptionsDescription& description() const);

private:
    std::vector<Option> parsedOptions;
    const OptionsDescription& desc;
};

OPT_NS_END

#endif
