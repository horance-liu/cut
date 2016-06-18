#ifndef CCINFRA_MEMORY_MSG_ALLOCATOR_H
#define CCINFRA_MEMORY_MSG_ALLOCATOR_H

#include <ccinfra/ccinfra.h>
#include <stddef.h>

CCINFRA_NS_BEGIN

struct MsgAllocator
{
    static void* alloc(size_t size);
    static void  free(void* p);
    static bool withIn(void* p);
};

CCINFRA_NS_END

#endif

