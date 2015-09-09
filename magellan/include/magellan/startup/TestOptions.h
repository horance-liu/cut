#ifndef INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4
#define INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4

#include <magellan/magellan.h>
#include "l0-infra/options/program_options/VariablesMap.hpp"
#include "l0-infra/options/program_options/OptionsDescription.hpp"

MAGELLAN_NS_BEGIN

struct TestOptions
{
    TestOptions();

    void parse(int argc, const char** argv);
    void clear();

    bool colorful() const;
    bool help() const;
    bool list() const;
    bool progress() const;
    bool xml() const;
    bool filter(const std::string& name) const;
    bool verbose() const;
    int repeat() const;

    const OPTIONS_NS::OptionsDescription& description() const;

private:
    bool matches(const std::string& name) const;

private:
    OPTIONS_NS::OptionsDescription desc;
    OPTIONS_NS::VariablesMap options;
};

MAGELLAN_NS_END

#endif
