#include "magellan/magellan.hpp"
#include <ccinfra/ctnr/map/HashMap.h>
#include <ccinfra/base/Keywords.h>
#include <string>

USING_HAMCREST_NS
USING_CCINFRA_NS

namespace
{
	struct MultipleValueMapVisitor : MapVisitor<int, int>
	{
		MultipleValueMapVisitor(int times) : times(times)
		{
		}

	private:
		OVERRIDE(Status visit(const int& key, int& value))
		{
			value = times * key;
			return CCINFRA_SUCCESS;
		}

	private:
		const int times;
	}multipleVisitor(3);

    struct PrintMapVisitor : ConstMapVisitor<int, const char*>
    {
        std::string result;

    private:
        OVERRIDE(Status visit(const int& key, const char* const& value))
        {
            std::stringstream ss;
            ss << "map[" << key <<"] = " << value << " \n";
            result += ss.str();
            return CCINFRA_SUCCESS;
        }
    }printVisitor;

    struct Key
    {
        Key(int x, int y)
        : x(x), y(y)
        {
        }

        size_t hash() const
        {
            return (x + y);
        }

        __INLINE_EQUALS(Key)
        {
            return (x == rhs.x) && (y == rhs.y);
        }

    private:
        int x;
        int y;
    };

    struct Value
    {
        Value() : value(__null_ptr){}
        Value(const char* v) : value(v)
        {
        }

        const char* getValue() const
        {
            return value;
        }

        bool operator==(const Value& rhs) const
        {
            return strcmp(value, rhs.value) == 0;
        }

    private:
        const char* value;
    };
}

namespace ccinfra
{
    template<size_t HASH_SIZE>
    struct HashFn<Key, HASH_SIZE>
    {
        size_t operator()(const Key& key) const
        {
            return key.hash();
        }
    };
}

FIXTURE(HashMapTest)
{

	TEST("should be empty when init")
	{
		HashMap<int, int> map;

		ASSERT_THAT(map.empty(), be_true());
		ASSERT_THAT(map.full(), be_false());
		ASSERT_THAT(map.size(), eq(0));
	}

	TEST("should get the value from key when inserted success")
	{
		HashMap<int, int> map;

		map.put(1, 2);
		map[2] = 4;

		ASSERT_THAT(map.empty(), be_false());
		ASSERT_THAT(map.full(), be_false());
		ASSERT_THAT(map.size(), eq(2));
		ASSERT_THAT(map[1], eq(2));
	}

	TEST("should erase the map correctly when only on node in map")
	{
		HashMap<int, int> map;

		map.put(1, 2);

		map.erase(1);

		ASSERT_THAT(map.empty(), be_true());
		ASSERT_THAT(map.size(), eq(0));
		ASSERT_THAT(map.get(1), is(nil()));
	}

	TEST("should erase the map correctly when muti node in map")
	{
		HashMap<int, int> map;

		map.put(1, 2);
		map.put(2, 4);

		map.erase(2);

		ASSERT_THAT(map.empty(), be_false());
		ASSERT_THAT(map.size(), eq(1));
		ASSERT_THAT(*map.get(1), eq(2));
		ASSERT_THAT(map.get(2), is(nil()));
	}

	TEST("should clear the map correctly")
	{
		HashMap<int, int> map;

		map.put(1, 2);
		map.put(2, 4);

		map.clear();

		ASSERT_THAT(map.empty(), be_true());
		ASSERT_THAT(map.size(), eq(0));
		ASSERT_THAT(map.get(1), is(nil()));
	}

	TEST("should not change the value when same key already in")
	{
		HashMap<int, int> map;

		map.put(1, 2);
		map.put(1, 4);

		ASSERT_THAT(map.size(), eq(1));
		ASSERT_THAT(map[1], eq(4));
	}

	TEST("should be full when reach the max node num")
	{
		HashMap<int, int, 1> map;

		ASSERT_THAT(__CCINFRA_SUCCESS(map.put(1, 2)), be_true());

		ASSERT_THAT(map.full(), be_true());
	}

	TEST("should put fail when map is full")
	{
		HashMap<int, int, 1> map;

		map.put(1, 2);
		ASSERT_THAT(__CCINFRA_FAILED(map.put(2, 2)), be_true());

		ASSERT_THAT(map.size(), eq(1));
		ASSERT_THAT(map[1], eq(2));
	}

	TEST("should put already in success when map is full")
	{
		HashMap<int, int, 1> map;

		map.put(1, 2);
		ASSERT_THAT(__CCINFRA_SUCCESS(map.put(1, 4)), be_true());

		ASSERT_THAT(map.size(), eq(1));
		ASSERT_THAT(map[1], eq(4));
	}

	TEST("should point to correct node by iterator when map is empty")
	{
		HashMap<int, int> map;

		ASSERT_THAT(map.begin().isNull(), be_true());
		ASSERT_THAT(map.end().isNull(), be_true());
	}

	TEST("should point to correct node by iterator when map has valid elem")
	{
		HashMap<int, int> map;

		map.put(1, 2);

		ASSERT_THAT(map.begin().isNull(), be_false());
		ASSERT_THAT(map.begin()->key, eq(1));
		ASSERT_THAT(map.begin()->value, eq(2));
		ASSERT_THAT(map.end().isNull(), be_true());
	}

	TEST("should point to correct node when iterator forward")
	{
		typedef HashMap<int, int> ThisMap;
		ThisMap map;

		map.put(1, 2);
		map.put(3, 6);

		ThisMap::Iterator p(map.begin());
		ASSERT_THAT(p++, eq(map.begin()));
		ASSERT_THAT(p.getValue()->key, eq(3));
		ASSERT_THAT(p.getValue()->value, eq(6));
		ASSERT_THAT(++p, eq(map.end()));
	}

	TEST("should travel the map by iterator")
	{
		typedef HashMap<int, int, 5, 5> ThisMap;
		ThisMap map;

		map.put(1, 2);
		map.put(3, 6);
		map.put(8, 16);
		map.put(5, 10);

		int keySum = 0;
		int valueSum = 0;

		MAP_FOREACH(ThisMap, i, map)
		{
			keySum += i->key;
			valueSum += i->value;
		}

		ASSERT_THAT(keySum, eq(1 + 3 + 8 + 5));
		ASSERT_THAT(valueSum, eq(2 + 6 + 16 + 10));
	}

	TEST("should put and get when hash string")
	{
		HashMap<const char*, int> map;

		map["hello"] = 5;
		map["ni hao ma"] = 9;

		ASSERT_THAT(map.size(), eq(2));
		ASSERT_THAT(map["hello"], eq(5));
		ASSERT_THAT(map["ni hao ma"], eq(9));
	}

	TEST("shoud double all value through visitor")
	{
		HashMap<int, int> map;

		map[1] = 1;
		map[2] = 2;

		map.visit(multipleVisitor);

		ASSERT_THAT(map[1], eq(3));
		ASSERT_THAT(map[2], eq(6));
	}

	TEST("should dump map through const visitor")
	{
		HashMap<int, const char*> map;

		map[1] = "one";
		map[2] = "two";
		map[3] = "three";

		map.visit(printVisitor);

		ASSERT_THAT(printVisitor.result, eq(std::string("map[1] = one \nmap[2] = two \nmap[3] = three \n")));
	}

	TEST("should work with user defined hash and equal function")
	{
		HashMap<Key, Value> map;

		map.put(Key(1, 3), Value("four"));
		map[Key(2, 3)] = Value("five");

		ASSERT_THAT(map[Key(1, 3)], eq(Value("four")));
		ASSERT_THAT(*map.get(Key(2, 3)), eq(Value("five")));
		ASSERT_THAT(map.get(Key(2, 4)), is(nil()));
	}

	TEST("should store the pointer to value")
	{
		Value v1("one");
		Value v2("two");

		HashMap<Key, Value*> map;

		map.put(Key(0, 1), &v1);
		map[Key(1, 1)] = &v2;

		ASSERT_THAT(map[Key(0, 1)], eq(&v1));
		ASSERT_THAT(*map.get(Key(1, 1)), eq(&v2));
		ASSERT_THAT(map.get(Key(2, 4)), is(nil()));
	}

};




