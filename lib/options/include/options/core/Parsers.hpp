#ifndef PARSERS_Thu_Apr_16_23_57_14_2015_H
#define PARSERS_Thu_Apr_16_23_57_14_2015_H

#include "options/core/OptionsDescription.hpp"
#include "options/core/Option.hpp"
#include "cub/dci/Role.h"
#include "options/core/Cmdline.hpp"

OPT_NS_BEGIN

struct OptionsDescription;

DEFINE_ROLE(ParsedOptions)
{
    ABSTRACT(const std::vector<Option>& options() const);
    ABSTRACT(const OptionsDescription& description() const);
};

struct CommandLineParser : private Cmdline, ParsedOptions{

    CommandLineParser( int argc, const char** argv
                     , const OptionsDescription& desc);

    const ParsedOptions& run();

private:
    OVERRIDE(const std::vector<Option>& options() const);
    OVERRIDE(const OptionsDescription& description() const);

private:
    std::vector<Option> parsedOptions;
    const OptionsDescription& desc;
};

OPT_NS_END

#endif
