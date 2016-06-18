#ifndef H5C910113_6FE0_4972_8A42_F9CC943F5B74
#define H5C910113_6FE0_4972_8A42_F9CC943F5B74

#include <ccinfra/ccinfra.h>
#include <ccinfra/base/ConstExpr.h>
#include <ccinfra/base/StaticAssert.h>
#include <ccinfra/base/EqHelper.h>
#include <ccinfra/utils/DefaultConstructor.h>
#include <type_traits>

CCINFRA_NS_BEGIN

template <typename T, size_t N>
struct Array
{
    typedef  Placement<T>   Elem;

    struct Iterator
    {
        Iterator() : elem(0)
        {
        }

        Iterator(Elem* elem) : elem(elem)
        {
        }

        Iterator(const Iterator& rhs) : elem(rhs.elem)
        {
        }

        Iterator& operator=(const Iterator& rhs)
        {
           elem = rhs.elem;
           return *this;
        }

        __INLINE_EQUALS(Iterator)
        {
            return (elem == rhs.elem);
        }

        void reset()
        {
           elem = 0;
        }

        bool isNull() const
        {
           return elem == 0;
        }

        T* operator->()
        {
           return getValue();
        }

        T& operator*()
        {
           return *getValue();
        }

        T* getValue() const
        {
            return &(elem->getRef());
        }

        Iterator operator++(int)
        {
           Iterator i = *this;

           elem++;

           return i;
        }

        Iterator& operator++()
        {
           elem++;

           return *this;
        }

    private:
        Elem* elem;
    };

    Array()
    {
        STATIC_ASSERT(N  > 0);
        STATIC_ASSERT(std::is_default_constructible<T>::value);

        DefaultConstructor<true>::construct(elems);
    }

    template<typename... ARGS>
    Array(ARGS&&... args)
    {
        for(size_t i = 0; i < N; ++i)
        {
            new (elems[i].alloc()) T(args...);
        }
    }

    CONST_EXPR size_t size() const
    {
        return N;
    }

    CONST_EXPR bool empty() const
    {
        return size() == 0;
    }

    const T& operator[](size_t index) const
    {
        return elems[index].getRef();
    }

    T& operator[](size_t index)
    {
        return elems[index].getRef();
    }

    template<typename... ARGS>
    void emplace(size_t index, ARGS&&... args)
    {
        if(index >= N) return;

        elems[index].destroy();
        new (elems[index].alloc()) T(args...);
    }

    Iterator begin()
    {
        return Iterator(&elems[0]);
    }

    Iterator end()
    {
        return Iterator(&elems[0] + N);
    }

private:
    Placement<T> elems[N];
};

/////////////////////////////////////////////////////////////
#define ARRAY_FOREACH_FROM(type, i, from, items) \
   for(typename type::Iterator i=from; i != items.end(); ++i)

#define ARRAY_FOREACH(type, i, items) \
   ARRAY_FOREACH_FROM(type, i, items.begin(), items)

CCINFRA_NS_END

#endif
