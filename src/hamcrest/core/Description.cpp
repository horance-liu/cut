#include <hamcrest/base/Description.h>
#include <hamcrest/base/SelfDescribing.h>

HAMCREST_NS_BEGIN

inline Description& Description::append(const std::string& text)
{
    desc += text;
    return *this;
}

Description& Description::appendText(const std::string& text)
{
    return append(text);
}

Description& Description::appendDescriptionOf(const SelfDescribing& value)
{
    value.describeTo(*this);
    return *this;
}

inline Description& Description::appendList
    ( const std::string& separator
    , const std::initializer_list<SelfDescribing> list)
{
    auto separate = false;
    for (auto &v : list)
    {
        if (separate) append(separator);
        appendDescriptionOf(v);
        separate = true;
    }
    return *this;
}

Description& Description::appendList
    ( const std::string& start
    , const std::string& separator
    , const std::string& end
    , const std::initializer_list<SelfDescribing> list)
{
    return append(start).appendList(separator, list).append(end);
}

HAMCREST_NS_END
