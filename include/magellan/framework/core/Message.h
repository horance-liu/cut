#ifndef H3FA1E1E1_4501_46E0_AAD7_11BDCEB8EAD7
#define H3FA1E1E1_4501_46E0_AAD7_11BDCEB8EAD7

#include <magellan/framework/magellan.h>
#include <string>
#include <vector>

MAGELLAN_NS_BEGIN

struct Message
{
private:
    using Details = std::vector<std::string>;

public:
    Message(std::string &&desc, Details&& = {});
    std::string str() const;

private:
    std::string desc;
    Details details;
};

MAGELLAN_NS_END

#endif
