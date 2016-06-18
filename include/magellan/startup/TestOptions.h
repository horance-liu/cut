#ifndef INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4
#define INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4

#include <magellan/magellan.h>
#include <ccinfra/dci/Role.h>
#include "ccinfra/options/program_options/VariablesMap.hpp"
#include "ccinfra/options/program_options/OptionsDescription.hpp"

MAGELLAN_NS_BEGIN

struct TestRunner;
struct TestListener;

DEFINE_ROLE(TestOptions)
{
    TestOptions();

    void parse(int argc, const char** argv);
    int run() const;
    void clear();

    TestListener* makeTextPrinter() const;
    TestListener* makeXmlPrinter() const;

    bool colorful() const;
    bool filter(const std::string& name) const;
    bool verbose() const;
    int repeat() const;

private:
    int help() const;
    int go() const;
    bool matches(const std::string& name) const;

private:
    cub::OptionsDescription desc;
    cub::VariablesMap options;

private:
    USE_ROLE(TestRunner);
};

MAGELLAN_NS_END

#endif
