#ifndef INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4
#define INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4

#include <magellan/magellan.h>
#include "l0-infra/options/ProgramOptions.hpp"

using options::OptionsDescription;
using options::VariablesMap;

MAGELLAN_NS_BEGIN

struct TestOption
{
    static TestOption& getInstance();

    void capatureOptionsFrom(int argc, const char** argv);

    bool hasHelpOption() const;
    void handlerHelpOption() const;

    bool handlerFilterOptionBy(const std::string& name) const;

private:
    TestOption();
    TestOption(const TestOption&);

    bool hasFilterOption() const;
    bool isMatchedName(const std::string& name) const;

private:
    OptionsDescription desc;
    VariablesMap& options;
};

MAGELLAN_NS_END

#endif
