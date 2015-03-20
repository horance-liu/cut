#ifndef _QHDGA6BWYYSJVRGHQ4OVYNFAJPUKWNH9188DUQXLQ36HRJF6RCSOJ41A               
#define _QHDGA6BWYYSJVRGHQ4OVYNFAJPUKWNH9188DUQXLQ36HRJF6RCSOJ41A

#define __DO_JOIN_AGAIN(symbol1, symbol2) symbol1##symbol2
#define __DO_JOIN(symbol1, symbol2) __DO_JOIN_AGAIN(symbol1, symbol2)

#define JOIN(symbol1, symbol2) __DO_JOIN(symbol1, symbol2)

#ifdef __COUNTER__
# define UNIQUE_NAME(prefix) JOIN(prefix, __COUNTER__)
#else
# define UNIQUE_NAME(prefix) JOIN(prefix, __LINE__)
#endif

#endif
