#ifndef SFDASDF_WERIUWT_347238_CNZXKAS_82348_QYAHHGF
#define SFDASDF_WERIUWT_347238_CNZXKAS_82348_QYAHHGF

#include <cut/cut.h>
#include <ostream>

CUT_NS_BEGIN

#define DECL_COLOR(color) \
const struct T_##color {  \
    T_##color() {};       \
} color; \
std::ostream& operator<<(std::ostream&, const T_##color&);

DECL_COLOR(WHITE)
DECL_COLOR(RED)
DECL_COLOR(GREEN)
DECL_COLOR(YELLOW)
DECL_COLOR(BLUE)
DECL_COLOR(MAGENTA)
DECL_COLOR(CYAN)

CUT_NS_END

#endif

