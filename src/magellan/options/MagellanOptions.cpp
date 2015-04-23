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
            , varMap(VariablesMap::getInstance())
            {
                desc.add({{"color,c", "print has color or not"}
                        , {"help,h", "print all options"}
                    });
                varMap.clear();
            }
        
        OVERRIDE(bool colorOn() const)
            {
                return true;
            }
        
        OVERRIDE(void parseArgs(int argc, const char** argv))
            {
                VariablesMap::getInstance().parseArgs(argc, argv, desc);
                if(varMap.has("help")) std::cout<<desc;
            }

    private:
        OptionsDescription desc;
        VariablesMap& varMap;
    };
}

MagellanOptions& MagellanOptions::getInstance()
{
    static MagellanOptionsImp imp;
    return imp;
}

MAGELLAN_NS_END
