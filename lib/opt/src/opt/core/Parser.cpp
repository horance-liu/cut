#include <opt/core/Cmdline.hpp>
#include <opt/core/OptionsDescription.hpp>
#include <opt/core/Parsers.hpp>
#include <opt/core/VariablesMap.hpp>

OPT_NS_BEGIN

CommandLineParser::	CommandLineParser
    ( int argc, const char** argv, const OptionsDescription& desc)
    : Cmdline(argc, argv), desc(desc)
{
}

const ParsedOptions&  CommandLineParser::run()
{
    Cmdline::setDescription(desc);

    parsedOptions = Cmdline::run();
    return *this;
}
    
const std::vector<Option>& CommandLineParser::opt() const
{
    return parsedOptions;
}
    
const OptionsDescription& CommandLineParser::description() const
{
    return desc;
}

OPT_NS_END
