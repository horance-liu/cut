#ifndef HB4FDA3F1_A2B1_407F_922D_FF7A05FBB0D4
#define HB4FDA3F1_A2B1_407F_922D_FF7A05FBB0D4

#include <hamcrest/base/hamcrest.h>
#include <infra/base/Formatter.h>

HAMCREST_NS_BEGIN

struct SelfDescribing;

struct Description
{
    Description& appendText(const std::string& text);
    Description& appendDescriptionOf(const SelfDescribing& value);

    template<typename T>
    Description& appendValue(const T& value)
    {
        desc += "<";
        desc += toTypeAndValueString(value);
        desc += ">";
        return *this;
    }

    Description& appendList
        ( const std::string& start
        , const std::string& separator
        , const std::string& end
        , const std::initializer_list<SelfDescribing> list);

private:
    Description& appendList
        ( const std::string& separator
        , const std::initializer_list<SelfDescribing> list);

    Description& append(const std::string&);

private:
    std::string desc;
};

HAMCREST_NS_END

#endif
