#include "magellan/infra/std/SourceFile.h"
#include <sstream>

STDEXT_NS_BEGIN

std::string source_file(const std::string& file, int line)
{
    std::stringstream ss;

    auto pos = file.find_last_of("/\\");
    pos == std::string::npos ? ss << file : ss << file.substr(++pos);

    ss << ":" << line;

    return ss.str();
}

STDEXT_NS_END
