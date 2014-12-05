#include "magellan/options/OptionsRepositry.h"
#include <vector>
#include <string.h>
#include <iostream>

MAGELLAN_NS_BEGIN

namespace 
{
    enum class Status
    {
        DONE,
        NOT_FOUND,
    };

    bool isEq(const char* left, const char* right)
    {
        return  (strcmp(left, right) == 0);
    }
    
    struct OptionImp
    {
        explicit OptionImp( const char* shortName // use -h
                            , const char* longName //
                            , const char* description) // "this is a help"
            : shortName(shortName), longName(longName), description(description)
        {
        
        }  

        bool match(const char* argv) const
        {
            return matchShortName(argv) || matchLongName(argv);
        }

        void saveOption() const
        {
            std::cout<<description<<std::endl;
        }

    private:
        bool matchShortName(const char* argv) const
        {
            return isEq(argv, shortName);
        }
        
        bool matchLongName(const char* argv) const
        {
            return isEq(argv, longName);
        }
        

    private:
        const char* shortName;
        const char* longName;
        const char* description;
    };

    void dumpInvalidArgv(const char* argv)
    {
        std::cout<<"this\""<<argv<<"\"is not avilable"<<std::endl;
    }    
}

static OptionImp help("-h", "--help", "this is a help");


struct OptionsRepositryImpl : OptionsRepositry
{
    OVERRIDE(void initArgs(char** argvList))
    {
        for(int i = 1; argvList[i] != 0x0; ++i)
        {
            auto& argv = argvList[i];
            if(!checkArgv(argv)) continue;
            if(saveOption(argv) == Status::NOT_FOUND)
            {
                dumpInvalidArgv(argv);
            }
        }
    }
    
    OptionsRepositryImpl()
    {
        optionList.push_back(help);
    }


private:
    bool checkArgv(const char* argv)
    {
        return argv[0] ==  '-';
    }
    
    Status saveOption(const char* argv)
    {
        for(auto option : optionList)
        {
            if(option.match(argv)) 
            {
                option.saveOption();
                return Status::DONE;
            }
        }
        return Status::NOT_FOUND;
    }
private:
   std::vector<OptionImp> optionList;
};

OptionsRepositry& OptionsRepositry::getInstance()
{
    static OptionsRepositryImpl impl;
    return impl;
}

MAGELLAN_NS_END
