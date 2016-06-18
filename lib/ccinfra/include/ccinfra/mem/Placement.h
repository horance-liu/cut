#ifndef H05B2224D_B926_4FC0_A123_97B52B8A99DB
#define H05B2224D_B926_4FC0_A123_97B52B8A99DB

#include <ccinfra/ccinfra.h>
#include <string.h>
#include <new>

CCINFRA_NS_BEGIN

template <typename T>
struct Placement
{
    Placement& operator=(const T& rhs)
    {
        assignBy(rhs);
        return *this;
    }

    void* alloc()
    {
        return (void*)&u;
    }

    T* operator->() const
    {
        return getObject();
    }

    T& operator*() const
    {
        return getRef();
    }

    T* getObject() const
    {
        return (T*)&u;
    }

    T& getRef() const
    {
        return (T&)u;
    }

    void destroy()
    {
        getObject()->~T();
    }

private:
    void assignBy(const T& rhs)
    {
        T* p = (T*)alloc();
        *p = rhs;
    }
private:
    union
    {
        char   c;
        short  s;
        int    i;
        long   l;
        long long   ll;
        float  f;
        double d;
        void*  p;

        char buff[sizeof(T)];
    }u;
};

template <typename T>
struct DefaultPlacement : Placement<T>
{
    T* init()
    {
        return new(Placement<T>::alloc()) T();
    }
};

CCINFRA_NS_END

#endif
