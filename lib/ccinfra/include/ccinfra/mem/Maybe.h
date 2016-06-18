#ifndef H05B2224D_B926_4FC1_A936_97B52B8A99DB
#define H05B2224D_B926_4FC1_A936_97B52B8A99DB

#include <ccinfra/mem/Placement.h>

CCINFRA_NS_BEGIN

template <typename T>
struct Maybe
{
    Maybe() : present(false) {}

    Maybe(const T& object) 
        : present(true) 
    {
        this->object = object;
    }

    ~Maybe()
    {
        reset();
    }

    Maybe& operator=(const Maybe& rhs)
    {
        present = rhs.present;
        if(present)
        {
            this->object = rhs.getRef();
        }

        return *this;
    }

    bool operator==(const Maybe& rhs) const
    {
        if(present != rhs.present) return false;
        if(!present) return true;
        return getRef() == rhs.getRef();
    }

    bool operator!=(const Maybe& rhs) const
    {
        return !(*this == rhs);
    }

    void update(const T& object)
    {
        present = true;
        this->object = object;
    }

    void forceEffective() 
    {
        if(!present)
        {
            present = true;
            new (object.alloc()) T();
        }
    }

    bool isPresent() const
    {
        return present;
    }

    /**
     * could be called only if is present.
     */
    const T& operator*() const
    {
        return *(object.getObject());
    }

    /**
     * could be called only if isPresent.
     */
    T& operator*()
    {
        return *(object.getObject());
    }

    const T* operator->() const
    {
        return getPointer();
    }

    T* operator->()
    {
        return getPointer();
    }

    const T* getPointer() const
    {
        return present ? object.getObject() : 0;
    }

    T* getPointer()
    {
        return present ? object.getObject() : 0;
    }

    T& getRef()
    {
        return *getPointer();
    }

    const T& getRef() const
    {
        return *getPointer();
    }

    void reset()
    {
        if(present)
        {
            present = false;
            object.destroy();
        }
    }

    size_t getOffsetOfPresent() const
    {
        return (char*)&present - (char*)this;
    }
private:
    Placement<T> object;
    bool present;
};

CCINFRA_NS_END

#endif

