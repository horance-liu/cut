#ifndef CCINFRA_MEMORY_SMART_PTR_H
#define CCINFRA_MEMORY_SMART_PTR_H

#include <ccinfra/dci/Role.h>
#include <ccinfra/mem/SharedObject.h>

CCINFRA_NS_BEGIN

template <typename OBJ>
struct SmartPtr
{
    SmartPtr() : p(0) {}
    SmartPtr(const OBJ* p) : p(const_cast<OBJ*>(p)) 
    {
        addRef();
    }

    SmartPtr(const SmartPtr& rhs) 
        : p(rhs.p)
    {
        addRef();
    }

    SmartPtr& operator=(const SmartPtr& rhs) 
    {
        release();

        p = rhs.p;
        addRef();

        return *this;
    }

    ~SmartPtr()
    {
        release();
    }

    bool operator==(const SmartPtr& rhs) const
    {
        return rhs.p == p;
    }

    bool operator!=(const SmartPtr& rhs) const
    {
        return !(*this == rhs);
    }

    OBJ* operator->()
    {
        return p;
    }

    const OBJ* operator->() const
    {
        return p;
    }

    bool isNull() const
    {
        return p == 0;
    }

    OBJ* raw() 
    {
        return p;
    }

    const OBJ* raw() const
    {
        return p;
    }

    OBJ& operator*()
    {
        return *p;
    }

    const OBJ& operator*() const
    {
        return *p;
    }

    void release()
    {
        if(p != 0)
        {
            p->ROLE(SharedObject).subRef();
            p = 0;
        }
    }

private:
    void addRef()
    {
        if(p != 0)
        {
            p->ROLE(SharedObject).addRef();
        }
    }

private:
    OBJ* p;
};

CCINFRA_NS_END

#endif
