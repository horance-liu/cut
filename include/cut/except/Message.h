#ifndef H3FA1E1E1_4501_46E0_AAD7_11BDCEB8EAD7
#define H3FA1E1E1_4501_46E0_AAD7_11BDCEB8EAD7

#include <cut/cut.h>
#include <string>
#include <vector>

CUT_NS_BEGIN

struct Message
{
    Message(const std::string& desc, const std::string& detail = "");
    const std::string& str() const;

private:
    std::string msg;
};

CUT_NS_END

#endif
