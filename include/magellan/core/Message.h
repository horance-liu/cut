#ifndef H3FA1E1E1_4501_46E0_AAD7_11BDCEB8EAD7
#define H3FA1E1E1_4501_46E0_AAD7_11BDCEB8EAD7

#include <magellan/base/magellan.h>
#include <string>
#include <vector>
#include <initializer_list>

MAGELLAN_NS_BEGIN

struct Message
{
    Message(const std::string &desc, const std::initializer_list<std::string> details = {});

    std::string str() const;

private:
    std::string desc;
    std::vector<std::string> details;
};

MAGELLAN_NS_END

#endif
