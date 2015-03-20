#include "magellan/framework/core/Message.h"
#include <sstream>

MAGELLAN_NS_BEGIN

Message::Message(const std::string &desc, const std::initializer_list<std::string> details)
  : desc(desc), details(details)
{
}

std::string Message::str() const
{
    std::stringstream ss;

    ss << desc;

    for (auto &detail : details)
    {
        if(detail.empty())
            break;

        ss << "-";
        ss << detail;
        ss << "\n";
    }

    return ss.str();
}

MAGELLAN_NS_END
