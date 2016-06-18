#include <ccinfra/log/log.h>
#include <ccinfra/base/BaseTypes.h>
#include <ccinfra/base/NullPtr.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

CCINFRA_NS_BEGIN

///////////////////////////////////////////////////////////////////////////
#define DEBUG_LEVEL     (U8)0x01
#define INFO_LEVEL      (U8)0x02
#define WARN_LEVEL      (U8)0x04
#define ERROR_LEVEL     (U8)0x08
#define FATAL_LEVEL     (U8)0x10

unsigned int Infra_Printf
    ( U16   /* module */
    , U32   /* errId */
    , U8     level
    , const void * format
    , ...);

namespace
{
    const char* getBaseName(const char* absPath)
    {
        if (absPath == 0) return "";

        const char* p = absPath + strlen(absPath);
        while ((p != absPath) && (*(p - 1) != '/'))
        {
            p--;
        }

        return p;
    }

    void logTrace( const char* file, U32 line, U8 prnLevel, const char* fmt, va_list paramList)
    {
        const  int   BUFF_SIZE = 350;

        char errInfo[BUFF_SIZE];

        if (fmt != __null_ptr)
        {
            vsnprintf(errInfo, BUFF_SIZE, fmt, paramList);
        }

        Infra_Printf( 0, 0, prnLevel, "%s:%lu: %s ", getBaseName(file), line, errInfo);
    }
}

#define DEF_LOG_TRACE(name, level)                                          \
void log_##name(const char* file, U32 line, const char* fmt, ...)           \
{                                                                           \
    va_list valist;                                                         \
    va_start(valist, fmt);                                                  \
    logTrace(file, line, level, fmt, valist);                               \
    va_end(valist);                                                         \
}

DEF_LOG_TRACE(fatal, FATAL_LEVEL);
DEF_LOG_TRACE(error, ERROR_LEVEL);
DEF_LOG_TRACE(warn,  WARN_LEVEL);
DEF_LOG_TRACE(info,  INFO_LEVEL);
DEF_LOG_TRACE(debug, DEBUG_LEVEL);

CCINFRA_NS_END
