#ifndef H24444E71_BA4A_444A_8ED4_03C92F43DBF5
#define H24444E71_BA4A_444A_8ED4_03C92F43DBF5

#include <cui/base/__Default__.h>

#define __ABSTRACT__(...) virtual __VA_ARGS__ = 0
#define __OVERRIDE__(...) virtual __VA_ARGS__

#define __EXTENDS__(...) , ##__VA_ARGS__
#define __IMPLEMENTS__(...) __EXTENDS__(__VA_ARGS__)

#endif

