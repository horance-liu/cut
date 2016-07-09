#include <cui/utils/__SourceFile__.h>
#include <sstream>

CUI_NS_BEGIN

namespace
{
    inline std::stringstream& basename(std::stringstream& ss, const std::string& name)
    {
        auto pos = name.find_last_of("/\\");
        pos == std::string::npos ? ss << name : ss << name.substr(++pos);

        return ss;
    }

    inline std::stringstream& fullname(std::stringstream& ss, const std::string& name)
    {
        ss << name;
        return ss;
    }

    inline std::stringstream& file(std::stringstream& ss, const std::string& name, bool absolute)
    {
        return absolute ? fullname(ss, name) : basename(ss, name);
    }
}

std::string sourcefile(const std::string& name, int line, bool absolute)
{
    std::stringstream ss;
    file(ss, name, absolute) << ":" << line;
    return ss.str();
}

CUI_NS_END
