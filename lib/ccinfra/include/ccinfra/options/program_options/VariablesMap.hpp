#ifndef VARIABLESMAP_Fri_Apr_10_22_02_27_2015_H
#define VARIABLESMAP_Fri_Apr_10_22_02_27_2015_H

#include "ccinfra/ccinfra.h"
#include <string>
#include <map>

CCINFRA_NS_BEGIN

struct OptionsDescription;
struct ParsedOptions;

struct VariablesMap
{
    void clear();
    void parseArgs( int argc, const char** argv, const OptionsDescription& desc);

    bool has(const std::string& name) const;

    const std::string& operator[](const std::string&) const;
    std::string& operator[](const std::string&);

    void dump() const;

private:
    void store(const ParsedOptions& options);

private:
    std::map<std::string, std::string> options;
};

CCINFRA_NS_END

#endif
