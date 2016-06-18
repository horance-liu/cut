#include <ccinfra/log/ConsoleState.h>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>

CCINFRA_NS_BEGIN

///////////////////////////////////////////////////////////
#define __RED     "\033[1;31m"
#define __GREEN   "\033[1;32m"
#define __YELLOW  "\033[1;33m"
#define __BLUE    "\033[1;34m"
#define __MAGENTA "\033[1;35m"
#define __CYAN    "\033[1;36m"
#define __WHITE   "\033[0m"

///////////////////////////////////////////////////////////
#define DEF_STATE_COLOR_MAPPING(S,C) \
std::ostream& operator<<(std::ostream& os, const S& state) \
{ \
   if(state.isColorful()) os << C; \
   return os; \
}

///////////////////////////////////////////////////////////
DEF_STATE_COLOR_MAPPING(SuccState,   __GREEN)
DEF_STATE_COLOR_MAPPING(InfoState,   __CYAN)
DEF_STATE_COLOR_MAPPING(WarnState,   __YELLOW)
DEF_STATE_COLOR_MAPPING(DebugState,  __MAGENTA)
DEF_STATE_COLOR_MAPPING(FailState,   __RED)
DEF_STATE_COLOR_MAPPING(NormalState, __WHITE)

namespace
{
    StdoutListener*  inst = 0;
}

StdoutListener* StdoutListener::create(bool colorful)
{
    if(inst == 0)
    {
        inst = new StdoutListener(colorful);
    }

    return inst;
}

StdoutListener& StdoutListener::getInstance()
{
    return *inst;
}

StdoutListener::StdoutListener(bool colorful)
        : succ(colorful)
        , fail(colorful)
        , normal(colorful)
        , info(colorful)
        , warn(colorful)
        , debug(colorful)
{
}

namespace
{
    enum
    {
        FT_DEBUG_LEVEL = 01,
        FT_INFO_LEVEL  = 02,
        FT_WARN_LEVEL  = 0x04,
        FT_ERR_LEVEL   = 0x08,
        FT_FATAL_LEVEL = 0x10
    };
}

template <typename STATE>
void StdoutListener::doPrint(const STATE& state, const char* msg)
{
    std::cout << state << msg << normal << std::endl ;
}

void StdoutListener::println(const U8 level, const char* msg)
{
    #define ON_LEVEL(level, state) case level: doPrint(state, msg); break;

    switch(level)
    {
    case FT_FATAL_LEVEL: doPrint(fail, msg); break;
    ON_LEVEL(FT_ERR_LEVEL,   fail)
    ON_LEVEL(FT_DEBUG_LEVEL, debug)
    ON_LEVEL(FT_INFO_LEVEL,  info)
    ON_LEVEL(FT_WARN_LEVEL,  warn)
    default: doPrint(normal, msg);
    }
}

//////////////////////////////////////////////////////////////////////////
unsigned int Infra_Printf
    ( U16   /* module */
    , U32   /* errId */
    , U8     level
    , const void * format
    , ...)
{
    va_list vaList;
    va_start(vaList, format);

    char buff[1024] = {0};
    vsnprintf(buff, 1024, (const char*)format, vaList);

    if(inst == 0) StdoutListener::create(true);
    StdoutListener::getInstance().println(level, buff);

    return 0;
}

CCINFRA_NS_END

