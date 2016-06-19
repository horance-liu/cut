#ifndef INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4
#define INCL_DCM_H7349D344_AAC4_47D0_8E42_DF1F7EC0C2A4

#include <cut/cut.h>
#include <cub/dci/Role.h>
#include <cpo/core/VariablesMap.hpp>
#include <cpo/core/OptionsDescription.hpp>

CUT_NS_BEGIN

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
    cpo::OptionsDescription desc;
    cpo::VariablesMap options;

private:
    USE_ROLE(TestRunner);
};

CUT_NS_END

#endif
