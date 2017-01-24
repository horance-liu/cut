#include <cum/base/Description.h>

CUM_NS_BEGIN

Description& Description::append(const std::string& text)
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

const std::string& Description::to_s() const
{
    return desc;
}

CUM_NS_END
