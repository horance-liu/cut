#include <cpo/core/OptionsDescription.hpp>
#include <cpo/core/Cmdline.hpp>
#include <cpo/core/Parsers.hpp>
#include <cpo/core/VariablesMap.hpp>

CPO_NS_BEGIN

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
    
const std::vector<Option>& CommandLineParser::options() const
{
    return parsedOptions;
}
    
const OptionsDescription& CommandLineParser::description() const
{
    return desc;
}

CPO_NS_END
