#ifndef CCINFRA_OBJECT_ALLOCATOR_H
#define CCINFRA_OBJECT_ALLOCATOR_H

#include "ccinfra/base/BaseTypes.h"
#include "ccinfra/base/Assertions.h"
#include <ccinfra/base/NullPtr.h>

CCINFRA_NS_BEGIN

template<typename T, U16 MAX_NUM>
struct ObjectAllocator
{
    ObjectAllocator() 
        : freeHead(__null_ptr)
        , freeTail(__null_ptr)
        , freeCounter(0)
    {
        for(U16 i = 0; i < MAX_NUM; i++)
        {
            freeEntity(entities[i]);
        }
    }

    U16 getFreeSlotNum() const
    {
        if (freeCounter < 0 || freeCounter > MAX_NUM)
        {
            return INVALID_U16;
        }

        return freeCounter;
    }

    bool hasFreeSlot() const
    {
        return freeHead != __null_ptr;
    }

    void* alloc()
    {
        if(!hasFreeSlot())
        {
            return __null_ptr;
        }
        return doAlloc();
    }

    void free(void* p)
    {
        if(p == __null_ptr) return;
        //if (isFree(p)) return; //important!, protect case :free a entity which has been freed

        CCINFRA_ASSERT_TRUE_VOID(within(p));
        CCINFRA_ASSERT_TRUE_VOID((((char*)p - (char*)entities) % sizeof(Entity)) == 0);

        freeEntity(*(Entity*)p);
    }

    bool within(void* p) const
    {
        return p >= (void*)entities && p < (void*)&(entities[MAX_NUM]);
    }

private:
    union Entity
    {
        char obj[sizeof(T)];
        Entity* next;
    };

private:

    void* doAlloc()
    {
        void* p = (void*)freeHead;

        freeHead = freeHead->next;

        if(freeHead == __null_ptr)
        {
            freeTail = __null_ptr;
        }

        freeCounter--;

        return p;
    }

    void freeEntity(Entity& entity)
    {
        if(freeHead == 0)
        {
            freeHead = &entity;
        }
        else
        {
            CCINFRA_ASSERT_VALID_PTR_VOID(freeTail);
            freeTail->next = &entity;
        }

        freeTail = &entity;
        freeTail->next = __null_ptr;
        freeCounter++;
    }

    bool isFree(const void* p) const
    {
        Entity* _header = freeHead;
        while (_header != __null_ptr)
        {
            if(_header == p) return true;
            _header = _header->next;
        }

        return false;
    }

private:
    Entity entities[MAX_NUM];
    Entity* freeHead;
    Entity* freeTail;
    U16  freeCounter;
};

//////////////////////////////////////////////////////////////////////////
#define DECL_OPERATOR_NEW()              \
void* operator new(size_t) throw();      \
void operator delete(void* p)

//////////////////////////////////////////////////////////////////////////
#define DEF_OPERATOR_NEW(p_type, allocator)                     \
    void* p_type::operator new(size_t) throw()                  \
    {                                                           \
       return allocator.alloc();                                \
    }                                                           \
    void p_type::operator delete(void* p)                       \
    {                                                           \
        allocator.free(p);                                      \
    }

//////////////////////////////////////////////////////////////////////////
#define DEF_GENERIC_OPERATOR_NEW(p_type, allocator)             \
    template <typename T>                                       \
    void* p_type<T>::operator new(size_t) throw()               \
    {                                                           \
       return allocator.alloc();                                \
    }                                                           \
    template <typename T>                                       \
    void p_type<T>::operator delete(void* p)                    \
    {                                                           \
        allocator.free(p);                                      \
    }


//////////////////////////////////////////////////////////////////////////
#define DEF_OBJ_ALLOCATOR(p_type, p_num)                        \
namespace {                                                     \
  ::CCINFRA_NS::ObjectAllocator<p_type, p_num> p_type##Allocator;\
}                                                               \
DEF_OPERATOR_NEW(p_type, p_type##Allocator)

CCINFRA_NS_END

#endif

