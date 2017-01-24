#include <cpo/core/Cmdline.hpp>

#include <cpo/core/OptionsDescription.hpp>
#include <cpo/core/OptionsDescription.hpp>
#include <cpo/core/Option.hpp>
#include <cpo/core/OptionsDescription.hpp>
#include <cui/dci/__Role__.h>

using namespace std;

CPO_NS_BEGIN

Cmdline::Cmdline(const vector<string>& args)
  : args(args), desc(0)
{
}

Cmdline::Cmdline(int argc, const char** argv)
 : args(argv+1, argv+argc+!argc), desc(0)
{
}

void Cmdline::setDescription(const OptionsDescription& desc)
{
    this->desc= &desc;
}

typedef std::vector<Option> (Cmdline::* style_parser)(const std::string&);

void Cmdline::doAllParser(const std::string& arg, vector<Option>& result)
{
    static style_parser style_parsers[] = {&Cmdline::parseLongOption
                                           , &Cmdline::parseShortOption};
    for(auto& parser : style_parsers)
    {
        const auto& next  = (this->*parser)(arg);

        if(next.empty()) continue;

        result.insert(result.begin(), next.begin(), next.end());
    }
}

vector<Option> Cmdline::run()
{
    vector<Option> result;
    for(const auto& arg : args)
    {
         doAllParser(arg, result);
    }
    return result;
}

namespace
{

    __TRAIT__(Tok)
    {
        __ABSTRACT__(void parse(string& name, string& adjacent) const);
    };

    struct LongTok : Tok
    {
        LongTok(const string& tok):tok(tok){}
    private:
        __OVERRIDE__(void parse( string& name, string& adjacent) const)
        {
             auto  p = tok.find('=');
             if (p != tok.npos)
             {
                  name = tok.substr(2, p-2);
                  adjacent = tok.substr(p);
             }
             else
             {
                  name = tok.substr(2);
             }
        }
    private:
        const string& tok;
    };

    struct BaseOptionParser
    {
         BaseOptionParser(const Tok& init, const OptionsDescription& desc )
           : desc(desc), foundOption(0)
         {
              init.parse(name, adjacent);
         }

         bool tryFind()
         {
              foundOption = desc.find(name);
              return foundOption != 0;
         }

         void addOption()
         {
              bool hasValue = (adjacent[0] == '=');
              auto getValue =  [&]{adjacent.erase(adjacent.begin());
                                   return adjacent;
              };
              result.push_back(Option(getName(), hasValue? getValue() : ""));
              if(hasValue) adjacent.clear();
         }

         const string& getName()
         {
              return foundOption ? foundOption->getLongName():name;
         }

         string name;
         string adjacent;
         vector<Option> result;
    private:
         const OptionsDescription& desc;
         const OptionDescription* foundOption;
    };


    struct LongOptionParser : BaseOptionParser
    {
         LongOptionParser(const string& tok, const OptionsDescription& desc)
              :BaseOptionParser(LongTok(tok), desc)
         {
              isLongOption = (tok.size() >= 3
                              && tok[0] == '-' && tok[1] == '-');
         }
         bool isLongOption;
    };
}

vector<Option> Cmdline::parseLongOption(const string& tok)
{
     LongOptionParser parser(tok, *desc);
     if (!parser.isLongOption) return parser.result;

     if(parser.tryFind())
     {
          parser.addOption();
     }

    return parser.result;
}

namespace
{

    struct ShortTok : Tok
    {
        ShortTok(const string& tok):tok(tok){}
    private:
        __OVERRIDE__(void parse(string& name, string& adjacent) const)
            {
                name = tok.substr(0,2);
                adjacent = tok.substr(2);
            }
    private:
        const string& tok;
    };

    struct ShortOptionParser : BaseOptionParser
    {
         ShortOptionParser(const string& tok, const OptionsDescription& desc)
              : BaseOptionParser(ShortTok(tok),desc)
         {
              isShortOption = (tok.size() >= 2
                               && tok[0] == '-' && tok[1] != '-');
         }

         bool finished() const
         {
              return adjacent.empty();
         }

         void goNext()
         {
              name = string("-") + adjacent[0];
              adjacent.erase(adjacent.begin());
         }

         bool isShortOption;
    };
}

vector<Option> Cmdline::parseShortOption(const string& tok)
{
    ShortOptionParser parser(tok, *desc);

    if (!parser.isShortOption)return parser.result;

    while(true)
    {
        if(parser.tryFind())
        {
            parser.addOption();
        }
        if(parser.finished()) break;
        parser.goNext();
    }
    return parser.result;
}

CPO_NS_END
