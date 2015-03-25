#include "magellan/except/Message.h"
#include <l0-infra/std/Algorithm.h>

MAGELLAN_NS_BEGIN

Message::Message(const std::string& desc, const std::string& detail)
   : msg(desc + "\n" + detail)
{
}

const std::string& Message::str() const
{
    return msg;
}

MAGELLAN_NS_END
