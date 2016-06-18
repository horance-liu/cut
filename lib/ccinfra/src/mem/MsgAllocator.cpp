#include <ccinfra/mem/MsgAllocator.h>
#include <ccinfra/mem/ObjectAllocator.h>

CCINFRA_NS_BEGIN

#if PERFORMANCE_OPTIMIZE

namespace
{
    const static U32 MEM_POOL_SIZE = 4*1024*1024;
    U32 index = 0;
    U8 pool[MEM_POOL_SIZE+201];

    void* memPoolAlloc(size_t size)
    {
        if((size>(MEM_POOL_SIZE - index)) || (index > MEM_POOL_SIZE))
        {
            index = 0;
        }

        void* p = pool + index;
        index += (size + 200);

        return p;
    }
}

void* MsgAllocator::alloc(size_t size)
{
    return memPoolAlloc(size);
}

void  MsgAllocator::free(void* p)
{
    return;
}

bool MsgAllocator::withIn(void* p)
{
    return (pool <= p) && (p < pool + MEM_POOL_SIZE);
}

#else

namespace
{
    template<size_t MEM_BLOCK_SIZE, U16 BLOCK_NUM>
    struct BlockAllocator
    {
        BlockAllocator()
        {

        }

        static void* alloc()
        {
            return allocator.alloc();
        }

        static void free(void* p)
        {
            allocator.free(p);
        }

        static bool tryAlloc(size_t size)
        {
            return (size <= MEM_BLOCK_SIZE) && (allocator.hasFreeSlot());
        }

        static bool tryFree(void *p)
        {
            PTR_VALUE lower_bound = (PTR_VALUE)(&allocator);
            PTR_VALUE upper_bound = lower_bound + MEM_BLOCK_SIZE*BLOCK_NUM;
            return (lower_bound <= (PTR_VALUE)p) && ((PTR_VALUE)p < upper_bound);
        }

    private:
        struct Block
        {
            char mem[MEM_BLOCK_SIZE];
        };

    private:
        static ObjectAllocator<Block, BLOCK_NUM> allocator;
    };

    template<size_t MEM_BLOCK_SIZE, U16 BLOCK_NUM>
    ObjectAllocator<typename BlockAllocator<MEM_BLOCK_SIZE, BLOCK_NUM>::Block, BLOCK_NUM> BlockAllocator<MEM_BLOCK_SIZE, BLOCK_NUM>::allocator;

    #define K(s) s * 1024

    typedef BlockAllocator<K(32),  16> Msg32KAllocator;
    typedef BlockAllocator<K(64),  8>  Msg64KAllocator;
    typedef BlockAllocator<K(128), 4>  Msg128KAllocator;
    typedef BlockAllocator<K(256), 2>  Msg256KAllocator;
    typedef BlockAllocator<K(512), 1>  Msg512KAllocator;
}

#define __BLOCK_NAME(n) Msg##n##KAllocator
#define TRY_BLOCK(n) if(__BLOCK_NAME(n)::tryAlloc(size))  return __BLOCK_NAME(n)::alloc()

void* MsgAllocator::alloc(size_t size)
{
    TRY_BLOCK(32);
    TRY_BLOCK(64);
    TRY_BLOCK(128);
    TRY_BLOCK(256);
    TRY_BLOCK(512);

    DBG_LOG("The specified size is too big for allocator, size = %d!", size);

    return 0;
}

#define TRY_FREE(n) if(__BLOCK_NAME(n)::tryFree(p))  return __BLOCK_NAME(n)::free(p)

void  MsgAllocator::free(void* p)
{
    TRY_FREE(32);
    TRY_FREE(64);
    TRY_FREE(128);
    TRY_FREE(256);
    TRY_FREE(512);

    DBG_LOG("The freed pointer(%x) is not in any MsgAllocator!", p);

    return;
}

#define WITH_IN(n) if(__BLOCK_NAME(n)::tryFree(p))  return true;

bool MsgAllocator::withIn(void* p)
{
    WITH_IN(32);
    WITH_IN(64);
    WITH_IN(128);
    WITH_IN(256);
    WITH_IN(512);

    return false;
}

CCINFRA_NS_END

#endif

