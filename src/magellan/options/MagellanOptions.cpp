#include "magellan/options/MagellanOptions.h"
#include "l0-infra/options/program_options/VariablesMap.hpp"
#include "l0-infra/options/program_options/OptionsDescription.hpp"
#include <iostream>

MAGELLAN_NS_BEGIN

USING_OPTIONS_NS

namespace
{
    struct MagellanOptionsImp : MagellanOptions
    {
        MagellanOptionsImp()
            : desc("Magellan")
            , options(VariablesMap::getInstance())
            {
                desc.add({
                    {"help , h ",   "help message"},
                    {"filter, f",  "set filter"},
                    {"color-off,c",   "output has color or not"},
                    {"format,x",     "output xml or term"},
                    {"path,d", "xml out path"}
                });
            }

        OVERRIDE(const std::string& getXmlPath()const)
        {
           return options["path"];
        }
        
        OVERRIDE(void capatureOptionsFrom(int argc, const char** argv))
        {
            options.parseArgs(argc, argv, desc);
        }

        OVERRIDE(bool outPutXml() const)
        {
            return options.has("format") && options["format"] == "xml";
        }

        OVERRIDE(bool colorOn() const)
        {
            return !options.has("color-off");
        }

        OVERRIDE(bool hasHelpOption() const)
        {
            return options.has("help");
        }

        OVERRIDE(void handlerHelpOption() const)
        {
            std::cout << desc;
        }

        OVERRIDE(bool handlerFilterOptionBy(const std::string& name) const)
        {
            return (!hasFilterOption())
                || (hasFilterOption() && isMatchedName(name));
        }

    private:
        bool hasFilterOption() const
        {
            return options.has("filter");
        }

        bool isMatchedName(const std::string& name) const
        {
            return name == options["filter"];  //To do: need fixed to support *
        }

    private:
        OptionsDescription desc;
        VariablesMap& options;
    };
}

MagellanOptions& MagellanOptions::getInstance()
{
    static MagellanOptionsImp imp;

    return imp;
}

MAGELLAN_NS_END
