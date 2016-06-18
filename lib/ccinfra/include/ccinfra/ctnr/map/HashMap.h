#ifndef HF41FC0CC_15A0_4F16_92AE_15D0759215A8
#define HF41FC0CC_15A0_4F16_92AE_15D0759215A8

#include <ccinfra/ctnr/map/HashFn.h>
#include <ccinfra/ctnr/map/EqualFn.h>
#include <ccinfra/ctnr/map/MapVisitor.h>
#include <ccinfra/ctnr/list/ListElem.h>
#include <ccinfra/ctnr/list/List.h>
#include <ccinfra/base/StaticAssert.h>
#include <ccinfra/base/EqHelper.h>
#include <ccinfra/mem/ObjectAllocator.h>
#include <ccinfra/algo/loop.h>
#include <ccinfra/base/ConstExpr.h>

CCINFRA_NS_BEGIN

template < typename KEY
         , typename VALUE
         , size_t   ELEM_SIZE = 1024
         , size_t   HASH_SIZE = ELEM_SIZE
         , typename HASH_FN = HashFn<KEY, HASH_SIZE>
         , typename EQUAL_FN = EqualFn<KEY> >
struct HashMap
{
    template <typename K, typename V>
    struct HashNode : ListElem< HashNode<K, V> >
    {
        HashNode(const K& k, const V& v)
        : key(k), value(v)
        {
        }

        K key;
        V value;
    };

    typedef HashNode<KEY, VALUE> Node;

    struct Iterator
    {
        Iterator()
        : elem(0), index(0), nodeList(0)
        {
        }

        Iterator(Node* elem, size_t index, const List<Node>* nodeList)
        : elem(elem), index(index), nodeList(nodeList)
        {
        }

        Iterator(const Iterator& rhs)
        : elem(rhs.elem), index(rhs.index), nodeList(rhs.nodeList)
        {
        }

        Iterator& operator=(const Iterator& rhs)
        {
            elem = rhs.elem;
            index = rhs.index;
            nodeList = rhs.nodeList;

            return *this;
        }

        __INLINE_EQUALS(Iterator)
        {
            return (elem == rhs.elem) &&
                   (index == rhs.index) &&
                   (nodeList == rhs.nodeList);
        }

        void reset()
        {
            elem = 0;
            index = 0;
            nodeList = 0;
        }

        bool isNull() const
        {
            return elem == 0;
        }

        Node* operator->()
        {
            return elem;
        }

        Node& operator*()
        {
            return *elem;
        }

        Node* getValue() const
        {
            return elem;
        }

        Iterator operator++(int)
        {
            Iterator i = *this;

            goNext();

            return i;
        }

        Iterator& operator++()
        {
            goNext();

            return *this;
        }

    private:
        void goNext()
        {
            if(elem == 0) return;

            isNeighborValid() ? goNeighbor(): goNextValid();
        }

        bool isNeighborValid() const
        {
            typename List<Node>::Iterator current(elem);
            typename List<Node>::Iterator next = nodeList[index].getNext(current);

            return next != nodeList[index].end();
        }

        void goNeighbor()
        {
            typename List<Node>::Iterator current(elem);
            elem = nodeList[index].getNext(current).getValue();
        }

        void goNextValid()
        {
            while(++index < HASH_SIZE)
            {
                if(!nodeList[index].isEmpty())
                {
                    elem = nodeList[index].getFirst();
                    return;
                }
            }

            elem = 0;
        }

    private:
        Node* elem;
        size_t index;
        const List<Node>* nodeList;
    };

    HashMap() : num(0)
    {
        STATIC_ASSERT(ELEM_SIZE > 0);
        STATIC_ASSERT(HASH_SIZE > 0);
    }

    Iterator begin() const
    {
        FOR_EACH_0(i, HASH_SIZE)
        {
            if(!buckets[i].isEmpty())
                return Iterator(buckets[i].getFirst(), i, buckets);
        }

        return Iterator(0, HASH_SIZE, buckets);
    }

    Iterator end() const
    {
        return Iterator(0, HASH_SIZE, buckets);
    }

    size_t size() const
    {
        return num;
    }

    CONST_EXPR size_t maxSize() const
    {
        return ELEM_SIZE;
    }

    bool empty() const
    {
        return num == 0;
    }

    bool full() const
    {
        return !allocator.hasFreeSlot();
    }

    const VALUE* get(const KEY& key) const
    {
        Node* node = find(key);
        if(__IS_NULL(node))
        {
            return __null_ptr;
        }

        return &(node->value);
    }

    Status put(const KEY& key, const VALUE& value)
    {
        const VALUE* v = get(key);

        if(__NOT_NULL(v))
        {
            *const_cast<VALUE*>(v) = value;
            return CCINFRA_SUCCESS;
        }

        return __IS_NULL(insert(key ,value)) ? CCINFRA_FAILURE : CCINFRA_SUCCESS;
    }

    VALUE& operator[](const KEY& key)
    {
        const VALUE* v = get(key);

        if(__NOT_NULL(v))
        {
            return *const_cast<VALUE*>(v);
        }

        return insert(key, VALUE())->value;
    }

    void erase(const KEY& key)
    {
        Node* node = find(key);

        if(__NOT_NULL(node))
        {
            buckets[getIndex(key)].remove(*node);
            allocator.free(node);
            num--;
        }
    }

    void clear()
    {
        FOR_EACH_0(i, HASH_SIZE)
        {
            while(Node* p = buckets[i].popFront())
            {
                allocator.free(p);
            }
        }

        num = 0;
    }

    Status visit(MapVisitor<KEY, VALUE>& visitor)
    {
        return access(visitor);
    }

    Status visit(ConstMapVisitor<KEY, VALUE>& visitor) const
    {
        return const_cast<HashMap&>(*this).access(visitor);
    }

private:
    template<typename VISITOR>
    Status access(VISITOR& visitor)
    {
        FOR_EACH_0(i, HASH_SIZE)
        {
            LIST_FOREACH(Node, node, buckets[i])
            {
                CCINFRA_ASSERT_SUCC_CALL(visitor.visit(node->key, node->value));
            }
        }

        return CCINFRA_SUCCESS;
    }

    size_t getIndex(const KEY &key) const
    {
        return hashFn(key) % HASH_SIZE;
    }

    Node* insert(const KEY& key, const VALUE& value)
    {
        void* p = allocator.alloc();
        if(__IS_NULL(p)) return __null_ptr;

        Node* node = new (p) Node(key, value);
        buckets[getIndex(key)].pushBack(*node);

        num++;

        return node;
    }

    Node* find(const KEY& key) const
    {
        Node* node = buckets[getIndex(key)].search(NodePred(key));
        if(__IS_NULL(node))
        {
            return __null_ptr;
        }

        return node;
    }

private:
    struct NodePred
    {
        NodePred(const KEY& key)
        : key(key)
        {
        }

        NodePred(const NodePred& other)
        : key(other.key)
        {
        }

        bool operator()(const Node& node) const
        {
            return EQUAL_FN()(node.key, key);
        }

    private:
        const KEY& key;
    };

private:
    typedef List<Node> Bucket;
    Bucket buckets[HASH_SIZE];
    unsigned int num;

    ObjectAllocator<Node, ELEM_SIZE> allocator;

private:
    HASH_FN  hashFn;
    EQUAL_FN equalFn;
};

/////////////////////////////////////////////////////////////
#define MAP_FOREACH_FROM(map_type, i, from, items) \
   for(typename map_type::Iterator i=from; i != items.end(); ++i)

#define MAP_FOREACH(map_type, i, items) \
   MAP_FOREACH_FROM(map_type, i, items.begin(), items)

CCINFRA_NS_END

#endif
