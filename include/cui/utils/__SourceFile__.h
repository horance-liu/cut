#ifndef HDA8AA766_B5CD_4F38_84C9_4D942908ABAD
#define HDA8AA766_B5CD_4F38_84C9_4D942908ABAD

#include <string>
#include <cui/cui.h>

CUI_NS_BEGIN

std::string sourcefile(const std::string& file, int line, bool absolute);

#define __SHORT_FILE__ ::CUI_NS::sourcefile(__FILE__, __LINE__, false)
#define __FULL_FILE__  ::CUI_NS::sourcefile(__FILE__, __LINE__, true)

CUI_NS_END

#endif
