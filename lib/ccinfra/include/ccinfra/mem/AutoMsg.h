#ifndef CCINFRA_MEMORY_AUTO_MSG_H
#define CCINFRA_MEMORY_AUTO_MSG_H

#include <ccinfra/mem/MsgNewOperator.h>
#include <ccinfra/mem/MsgAllocator.h>

CCINFRA_NS_BEGIN

template <typename MSG, typename MSG_ALLOCATOR>
struct GenericMsg : MSG, MsgNewOperator<MSG_ALLOCATOR>
{
};

template <typename MSG, typename MSG_ALLOCATOR = MsgAllocator>
struct AutoMsg
{
    AutoMsg()
    {
        msg = new GenericMsg<MSG, MSG_ALLOCATOR>;        
    }

    ~AutoMsg()
    {
        if(msg != 0)
        {
            msg->operator delete((void*)msg);
            msg = 0;
        }
    }

    MSG* operator->()
    {
        return msg;
    }

    const MSG* getPointer() const
    {
        return msg;
    }

    MSG* getPointer()
    {
        return msg;
    }

    const MSG& getRef() const
    {
        return *msg;
    }

    MSG& getRef()
    {
        return *msg;
    }

private:
    GenericMsg<MSG, MSG_ALLOCATOR>* msg;
};

CCINFRA_NS_END

#endif

