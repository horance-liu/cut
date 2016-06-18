#ifndef H38247538_297F_4A80_94D3_8A289788461B
#define H38247538_297F_4A80_94D3_8A289788461B

#include <ccinfra/ccinfra.h>

CCINFRA_NS_BEGIN

#define DECl_LOG(level) \
extern void log_##level(const char* file, unsigned int line, const char* fmt, ...)

DECl_LOG(fatal);
DECl_LOG(error);
DECl_LOG(debug);
DECl_LOG(info);
DECl_LOG(warn);

#define __LOG_TITLE(level, fmt, ...)                     \
log_##level(__FILE__, __LINE__, fmt, ##__VA_ARGS__);


#define FATAL_LOG(fmt, ...) \
    __LOG_TITLE(fatal, fmt, ##__VA_ARGS__)

#define ERR_LOG(fmt, ...) \
    __LOG_TITLE(error, fmt, ##__VA_ARGS__)

#define WARN_LOG(fmt, ...) \
    __LOG_TITLE(warn,  fmt, ##__VA_ARGS__)

#define INFO_LOG(fmt, ...) \
    __LOG_TITLE(info,  fmt, ##__VA_ARGS__)

#define DBG_LOG(fmt, ...) \
    __LOG_TITLE(debug, fmt, ##__VA_ARGS__)

CCINFRA_NS_END

#endif
