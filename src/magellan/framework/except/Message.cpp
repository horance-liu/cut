#include "magellan/framework/except/Message.h"
#include <sstream>

MAGELLAN_NS_BEGIN

Message::Message(std::string&& desc, Details&& details)
  : desc(std::move(desc)), details(std::move(details))
{}

std::string Message::str() const
{
    std::stringstream ss;

    ss << desc << "\n";

    for (auto &detail : details)
    {
        if(!detail.empty())
        {
            ss << " - " << detail << "\n";
        }
    }

    return ss.str();
}

MAGELLAN_NS_END
