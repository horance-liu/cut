#ifndef HC57E2472_2513_4E94_AEC6_067A30876304
#define HC57E2472_2513_4E94_AEC6_067A30876304

#include <string>
#include <mango/infra/std/stdext.h>

STDEXT_NS_BEGIN

std::string source_file(const std::string& file, int line, bool absolute);

#define SHORT_FILE() stdext::source_file(__FILE__, __LINE__, false)
#define FULL_FILE() stdext::source_file(__FILE__, __LINE__, true)

STDEXT_NS_END


#endif
