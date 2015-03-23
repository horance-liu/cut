#include "magellan/framework/except/Message.h"
#include <magellan/infra/std/Algorithm.h>

MAGELLAN_NS_BEGIN

Message::Message(const std::string& desc, const std::string& detail)
   : desc(desc), detail(detail)
{
//    printf("Message::desc:%s\n", desc.c_str());
//    printf("Message::detail:%s\n", detail.c_str());
}

std::string Message::str() const
{
    return desc + "\n" + detail;
}

MAGELLAN_NS_END
