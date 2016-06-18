#include <cut/listener/util/Color.h>
#include <cut/startup/TestOptions.h>
#include <cut/hook/runtime/Runtime.h>

CUT_NS_BEGIN

///////////////////////////////////////////////////////////
#if defined(_MSC_VER)

#include <windows.h>

///////////////////////////////////////////////////////////
#define C_RED     (FOREGROUND_RED   | FOREGROUND_INTENSITY)
#define C_BLUE    (FOREGROUND_BLUE  | FOREGROUND_INTENSITY)
#define C_GREEN   (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define C_YELLOW  (FOREGROUND_RED   | FOREGROUND_GREEN |FOREGROUND_INTENSITY)
#define C_MAGENTA (FOREGROUND_RED   | FOREGROUND_BLUE  |FOREGROUND_INTENSITY)
#define C_CYAN    (FOREGROUND_GREEN | FOREGROUND_BLUE  |FOREGROUND_INTENSITY)
#define C_WHITE   (FOREGROUND_RED   | FOREGROUND_BLUE  |FOREGROUND_GREEN )

///////////////////////////////////////////////////////////
namespace 
{
   struct Color
   {
      Color(unsigned int color) : color(color)
	  {}

      void operator()(void) const
      {
         ::SetConsoleTextAttribute
            ( ::GetStdHandle(STD_OUTPUT_HANDLE)
            , color);
      }

   private:
      unsigned int color;
   };
}

///////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Color& color)
{
    color();
    return os;
}

#define __RED     Color(C_RED)
#define __GREEN   Color(C_GREEN)
#define __YELLOW  Color(C_YELLOW)
#define __BLUE    Color(C_BLUE)
#define __MAGENTA Color(C_MAGENTA)
#define __CYAN    Color(C_CYAN)
#define __WHITE   Color(C_WHITE)

#else

#define __RED     "\033[1;31m"
#define __GREEN   "\033[1;32m"
#define __YELLOW  "\033[1;33m"
#define __BLUE    "\033[1;34m"
#define __MAGENTA "\033[1;35m"
#define __CYAN    "\033[1;36m"
#define __WHITE   "\033[0m"

#endif

///////////////////////////////////////////////////////////
#define DEF_COLOR(color)                                     \
std::ostream& operator<<(std::ostream& os, const T_##color&) \
{                                                            \
    if(!RUNTIME(TestOptions).colorful()) return os;   \
    return os << __##color;                                  \
}

///////////////////////////////////////////////////////////
DEF_COLOR(WHITE)
DEF_COLOR(RED)
DEF_COLOR(GREEN)
DEF_COLOR(YELLOW)
DEF_COLOR(BLUE)
DEF_COLOR(MAGENTA)
DEF_COLOR(CYAN)

CUT_NS_END
