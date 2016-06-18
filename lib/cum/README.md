# Hamcrest

Hamcrest是Java社区一个轻量级的，可扩展的Matcher框架，曾被Kent Beck引入到JUnit框架中，用于增强断言的机制。cut引入了Hamcrest的设计，实现了一个C\+\+移植版本的Hamcrest，使得cutg的断言更加具有扩展性和可读性。

## anything

| 匹配器         | 说明           |
| ------------- |---------------|
| anything      | 总是匹配       |
| _             | anything语法糖 |

```cpp
#include <cut/cut.hpp>

USING_CUM_NS

FIXTURE(AnythingTest)
{
    TEST("should always be matched")
    {
        ASSERT_THAT(1, anything<int>());
        ASSERT_THAT(1u, anything<unsigned int>());
        ASSERT_THAT(1.0, anything<double>());
        ASSERT_THAT(1.0f, anything<float>());
        ASSERT_THAT(false, anything<bool>());
        ASSERT_THAT(true, anything<bool>());
        ASSERT_THAT(nullptr, anything<std::nullptr_t>());
    }

    TEST("should support _ as syntactic sugar")
    {
        ASSERT_THAT(1u, _(int));
        ASSERT_THAT(1.0f, _(float));
        ASSERT_THAT(false, _(int));
        ASSERT_THAT(nullptr, _(std::nullptr_t));
    }
};
```

## 比较器

| 匹配器         | 说明            |
| ------------- |----------------|
| eq            | 相等              |
| ne            | 不相等          |
| lt            | 小于              |
| gt            | 大于              |
| le            | 小于或等于       |
| ge            | 大于或等于       |

```cpp
#include <cut/cut.hpp>

USING_CUM_NS

FIXTURE(EqualToTest)
{
    TEST("should allow compare to integer")
    {
        ASSERT_THAT(0xFF, eq(0xFF));
        ASSERT_THAT(0xFF, is(eq(0xFF)));

        ASSERT_THAT(0xFF, is(0xFF));
        ASSERT_THAT(0xFF == 0xFF, is(true));
    }

    TEST("should allow compare to bool")
    {
        ASSERT_THAT(true, eq(true));
        ASSERT_THAT(false, eq(false));
    }

    TEST("should allow compare to string")
    {
        ASSERT_THAT("hello", eq("hello"));
        ASSERT_THAT("hello", eq(std::string("hello")));
        ASSERT_THAT(std::string("hello"), eq(std::string("hello")));
    }
};

FIXTURE(NotEqualToTest)
{
    TEST("should allow compare to integer")
    {
        ASSERT_THAT(0xFF, ne(0xEE));

        ASSERT_THAT(0xFF, is_not(0xEE));
        ASSERT_THAT(0xFF, is_not(eq(0xEE)));
        ASSERT_THAT(0xFF != 0xEE, is(true));
    }

    TEST("should allow compare to boolean")
    {
        ASSERT_THAT(true, ne(false));
        ASSERT_THAT(false, ne(true));
    }

    TEST("should allow compare to string")
    {
        ASSERT_THAT("hello", ne("world"));
        ASSERT_THAT("hello", ne(std::string("world")));
        ASSERT_THAT(std::string("hello"), ne(std::string("world")));
    }
};
```

## 修饰器

| 匹配器         | 说明            |
| ------------- |----------------|
| is            | 可读性装饰器     |
| is_not        | 可读性装饰器     |

```cpp
#include <cut/cut.hpp>

USING_CUM_NS

FIXTURE(IsNotTest)
{
    TEST("integer")
    {
        ASSERT_THAT(0xFF, is_not(0xEE));
        ASSERT_THAT(0xFF, is_not(eq(0xEE)));
    }

    TEST("string")
    {
        ASSERT_THAT("hello", is_not("world"));
        ASSERT_THAT("hello", is_not(eq("world")));

        ASSERT_THAT("hello", is_not(std::string("world")));
        ASSERT_THAT(std::string("hello"), is_not(std::string("world")));
    }
};
```

##  空指针

| 匹配器         | 说明            |
| ------------- |----------------|
| nil           | 空指针          |

```cpp
#include <cut/cut.hpp>

USING_CUM_NS

FIXTURE(NilTest)
{
    TEST("equal_to")
    {
        ASSERT_THAT(nullptr, eq(nullptr));
        ASSERT_THAT(0, eq(NULL));
        ASSERT_THAT(NULL, eq(NULL));
        ASSERT_THAT(NULL, eq(0));
    }

    TEST("is")
    {
        ASSERT_THAT(nullptr, is(nullptr));
        ASSERT_THAT(nullptr, is(eq(nullptr)));

        ASSERT_THAT(0, is(0));
        ASSERT_THAT(NULL, is(NULL));
        ASSERT_THAT(0, is(NULL));
        ASSERT_THAT(NULL, is(0));
    }

    TEST("nil")
    {
        ASSERT_THAT((void*)NULL, nil());
        ASSERT_THAT((void*)0, nil());
        ASSERT_THAT(nullptr, nil());
    }
};
```

## 字符串

| 匹配器                      | 说明                          |
| ----------------------------- |----------------------------|
| contains_string               | 断言是否包含子串              |
| contains_string_ignoring_case | 忽略大小写，断言是否包含子      |
| starts_with                   | 断言是否以该子串开头           |
| starts_with_ignoring_case     | 忽略大小写，断言是否以该子串开头 |
| ends_with                     | 断言是否以该子串结尾             |
| ends_with_ignoring_case       | 忽略大小写，断言是否以该子串结尾 |

```cpp
#include <cut/cut.hpp>

USING_CUM_NS

FIXTURE(StartsWithTest)
{
    TEST("case sensitive")
    {
        ASSERT_THAT("ruby-cpp", starts_with("ruby"));
        ASSERT_THAT("ruby-cpp", is(starts_with("ruby")));

        ASSERT_THAT(std::string("ruby-cpp"), starts_with("ruby"));
        ASSERT_THAT("ruby-cpp", starts_with(std::string("ruby")));
        ASSERT_THAT(std::string("ruby-cpp"), starts_with(std::string("ruby")));
    }

    TEST("ignoring case")
    {
        ASSERT_THAT("ruby-cpp", starts_with_ignoring_case("Ruby"));
        ASSERT_THAT("ruby-cpp", is(starts_with_ignoring_case("Ruby")));

        ASSERT_THAT(std::string("ruby-cpp"), starts_with_ignoring_case("RUBY"));
        ASSERT_THAT("Ruby-Cpp", starts_with_ignoring_case(std::string("rUBY")));
        ASSERT_THAT(std::string("RUBY-CPP"), starts_with_ignoring_case(std::string("ruby")));
    }
};
```

## 浮点数

| 匹配器    | 说明                 |
| ---------|----------------------|
| close_to | 断言浮点数近似等于     |
| nan      | 断言浮点数不是一个数字   |

```cpp
#include <cut/cut.hpp>
#include <math.h>

USING_CUM_NS

FIXTURE(IsNanTest)
{
    TEST("double")
    {
        ASSERT_THAT(sqrt(-1.0), nan());
        ASSERT_THAT(sqrt(-1.0), is(nan()));

        ASSERT_THAT(1.0/0.0,  is_not(nan()));
        ASSERT_THAT(-1.0/0.0, is_not(nan()));
    }
};
```
