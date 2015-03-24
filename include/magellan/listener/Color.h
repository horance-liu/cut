#ifndef SFDASDF_WERIUWT_347238_CNZXKAS_82348_QYAHHGF
#define SFDASDF_WERIUWT_347238_CNZXKAS_82348_QYAHHGF

#include <magellan/magellan.h>
#include <ostream>

MAGELLAN_NS_BEGIN

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

MAGELLAN_NS_END

#endif

