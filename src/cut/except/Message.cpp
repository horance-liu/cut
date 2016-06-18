#include <cut/except/Message.h>

CUT_NS_BEGIN

Message::Message(const std::string& desc, const std::string& detail)
   : msg(desc + "\n" + detail)
{
}

const std::string& Message::str() const
{
    return msg;
}

CUT_NS_END
