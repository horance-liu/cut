# cut: A Simple xUnit Test Framework in Modern C++11

## 灵感

cut是一个简单的、可扩展的、使用C\+\+11实现的xUnit测试框架。cut设计灵感来自于Java社区著名的测试框架JUnit。

## 安装

### GitHub

- 地址：[https://github.com/horance-liu/cut](https://github.com/horance-liu/cut)
- 作者：刘光聪
- Email：[horance@outlook.com](horance@outlook.com)

### 编译环境

支持的平台:
* [MAC OS X] supported
* [Linux] supported
* [Windows] not supported

支持的编译器:
* [CLANG] 3.4 or later.
* [GCC] 4.8 or later.
* [MSVC] not supported.


### 克隆cut

```bash
$ git clone https://github.com:ccup/cut.git
```

### 安装依赖

> 当前路径：`cut`所在目录

```bash
$ git clone https://github.com/ccup/cub.git lib/cub
$ cd lib/cub && mkdir build && cd build
$ cmake .. && make
$ sudo make install 
```

### 安装cut

安装`cum`：

> 当前路径：`cut`所在目录

```bash
$ cd lib/cum && mkdir build && cd build
$ cmake .. && make
$ sudo make install 
```

安装`opt`：

> 当前路径：`cut`所在目录

```bash
$ cd lib/opt && mkdir build && cd build
$ cmake .. && make
$ sudo make install 
```

最后安装`cut`：

> 当前路径：`cut`所在目录

```bash
$ mkdir build && cd build
$ cmake .. && make
$ sudo make install 
```

##### 测试cut

> 当前路径：`cut`所在目录

```bash
$ cd build
$ cmake -DENABLE_TEST=on .. && make
$ test/cut-test
```

##### 使用Rake

使用`Rake`可简化`Magelan`的依赖管理，方便`cut`的构建，及其测试，并且使得`cut`自我测试变成更加方便自如。

> 当前路径：`cut`所在目录

```bash
$ rake deps      # install all dependencies
```

如果使用`GCC`，安装依赖可以如下命令完成：

```bash
$ rake clone    # clone all dependencies
$ rake build[gcc]    # clone all dependencies
```

其他`rake`任务包括：

```bash
$ rake             # build, install cut using clang
$ rake build       # build, install using clang
$ rake test        # build, install, and test using clang
$ rake build[gcc]  # build, install using gcc
$ rake test[gcc]   # build, install, and test using gcc
$ rake uninstall   # uninstall cut only
$ rake clean       # remove temp directory, and uninstall cut
```

其他依赖的`rake`任务包括：

```bash
$ rake deps        # clone, build, install all dependencies using clang
$ rake deps_clone  # clone all dependencies
$ rake deps_build  # clone, build, install all dependencies using clang
$ rake deps_test   # clone, build, install, and test all dependencies using clang

$ rake deps_build[gcc]  # clone, build, install all dependencies using gcc
$ rake deps_test[gcc]   # clone, build, install, and test all dependencies using gcc

$ rake deps_uninstall   # uninstall all dependencies
$ rake deps_clean       # remove temp directory, and uninstall all dependencies
```

### 破冰之旅

##### 物理目录

```bash
quantity
├── include
│   └── quantity
├── src
│   └── quantity
└── test
│   ├── main.cpp
└── CMakeLists.txt
```

##### main函数

```cpp
#include <cut/cut.hpp>

int main(int argc, char** argv)
{
    return cut::run_all_tests(argc, argv);
}
```

##### CMakeList脚本

```cmake
project(quantity)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE all_files
src/*.cpp
src/*.cc
src/*.c
test/*.cpp
test/*.cc
test/*.c)

add_executable(quantity-test ${all_files})

target_link_libraries(quantity-test cut cum opt cub)
```

其中：

- cut: C++ Unified Test framework;
- cum: C++ Universal Matchers;
- opt: C++ Program Options;
- cub: C++ Unified Base Libary;

##### 构建

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

##### 运行

```bash
$ ./quantity-test

[==========] Running 0 test cases.
[----------] 0 tests from All Tests
[----------] 0 tests from All Tests

[==========] 0 test cases ran.
[  TOTAL   ] PASS: 0  FAILURE: 0  ERROR: 0  TIME: 0 us
```

### 体验cut

#### 第一个用例

```cpp
#include <cut/cut.hpp>
#include <quantity/Length.h>

USING_CUM_NS

FIXTURE(LengthTest)
{
    TEST("1 FEET should equal to 12 INCH")
    {
        ASSERT_THAT(Length(1, FEET), eq(Length(12, INCH)));
    }
};
```

使用`cut`时，只需要包含`cut.hpp`一个头文件即可。`cut`使用`cum`的断言机制, 使得断言更加统一、自然,且具有良好的扩展性;使用 `USING_CUM_NS`, 从而可以使用 `eq` 代替 `cum::eq`,简短明确;除非出现名字冲突,否则推荐使用简写的`eq`。

#### Length实现

```cpp
// quantity/Length.h
#include <quantity/Amount.h>

enum LengthUnit
{
    INCH = 1,
    FEET = 12 * INCH,
};

struct Length
{
    Length(Amount amount, LengthUnit unit);

    bool operator==(const Length& rhs) const;
    bool operator!=(const Length& rhs) const;

private:
    const Amount amountInBaseUnit;
};
```

```cpp
// quantity/Length.cpp
#include <quantity/Length.h>

Length::Length(Amount amount, LengthUnit unit)
  : amountInBaseUnit(unit * amount)
{
}

bool Length::operator==(const Length& rhs) const
{
    return amountInBaseUnit == rhs.amountInBaseUnit;
}

bool Length::operator!=(const Length& rhs) const
{
    return !(*this == rhs);
}
```

##### 构建

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

##### 运行

```bash
$ ./quantity-test

[==========] Running 1 test cases.
[----------] 1 tests from All Tests
[----------] 1 tests from LengthTest
[ RUN      ] LengthTest::1 FEET should equal to 12 INCH
[       OK ] LengthTest::1 FEET should equal to 12 INCH(13 us)
[----------] 1 tests from LengthTest

[----------] 1 tests from All Tests

[==========] 1 test cases ran.
[  TOTAL   ] PASS: 1  FAILURE: 0  ERROR: 0  TIME: 13 us
```

### Fixture

FIXTURE的参数可以是任意的C\+\+标识符。一般而言，将其命名为CUT(Class Under Test)的名字即可。根据作用域的大小，Fixture可分为三个类别：独立的Fixture，共享的Fixture，全局的Fixture。

#### 支持BDD风格

| xUnit         | BDD           |
| ------------- |---------------|
| FIXTURE       | CONTEXT       |
| SETUP         | BEFORE        |
| TEARDOWN      | AFTER         |
| ASSERT_THAT   | EXPECT        |

#### 独立的Fixture

```cpp
#include <cut/cut.hpp>

FIXTURE(LengthTest)
{
    Length length;

    SETUP()
    {}

    TEARDOWN()
    {}

    TEST("length test1")
    {}

    TEST("length test2")
    {}
};
```

执行序列为：
1. `Length` 构造函数
2. `SETUP`
3. `TEST("length test1")`
4. `TEARDOWN`
5. `Length` 析构函数
6. `Length` 构造函数
7. `SETUP`
8. `TEST("length test2")`
9. `TEARDOWN`
10. `Length` 析构函数


#### 共享的Fixture

```cpp
#include <cut/cut.hpp>

FIXTURE(LengthTest)
{
    Length length;

    BEFORE_CLASS()
    {}

    AFTER_CLASS()
    {}

    BEFORE()
    {}

    AFTER()
    {}

    TEST("length test1")
    {}

    TEST("length test2")
    {}
};
```

执行序列为：
1. `BEFORE_CLASS`
2. `Length` 构造函数
3. `BEFORE`
4. `TEST("length test1")`
5. `AFTER`
6. `Length` 析构函数
7. `Length` 构造函数
8. `BEFORE`
9. `TEST("length test2")`
10. `AFTER`
11. `Length` 析构函数
12. `AFTER_CLASS`

#### 全局的Fixture

有时候需要在所有用例启动之前完成一次性的全局性的配置，在所有用例运行完成之后完成一次性的清理工作。cut则使用`BEFORE_ALL`和`AFTER_ALL`两个关键字来支持这样的特性。

```cpp
#include <cut/cut.hpp>

BEFORE_ALL("before all 1")
{
}

BEFORE_ALL("before all 2")
{
}

AFTER_ALL("after all 1")
{
}

AFTER_ALL("after all 2")
{
}
```

`BEFORE_ALL`和`AFTER_ALL`向系统注册`Hook`即可，cut便能自动地发现它们，并执行它们。犹如C\+\+不能保证各源文件中全局变量初始化的顺序一样，避免在源文件之间的`BEFORE_ALL`和`AFTER_ALL`设计不合理的依赖关系。

```cpp
#include <cut/cut.hpp>

FIXTURE(LengthTest)
{
    Length length;

    BEFORE_CLASS()
    {}

    AFTER_CLASS()
    {}

    BEFORE()
    {}

    AFTER()
    {}

    TEST("length test1")
    {}

    TEST("length test2")
    {}
};
```

```cpp
#include <cut/cut.hpp>

FIXTURE(VolumeTest)
{
    Volume volume;

    BEFORE_CLASS()
    {}

    AFTER_CLASS()
    {}

    BEFORE()
    {}

    AFTER()
    {}

    TEST("volume test1")
    {}

    TEST("volume test1")
    {}
};
```

cut可能的一个执行序列为：

1. `BEFORE_ALL("before all 1")`
2. `BEFORE_ALL("before all 2")`
3. `LengthTest::BEFORE_CLASS`
4. `Length`构造函数
5. `LengthTest::BEFORE`
6. `TEST("length test1")`
7. `LengthTest::AFTER`
8. `Length`析构函数
9. `Length`构造函数
10. `LengthTest::BEFORE`
11. `TEST("length test2")`
12. `LengthTest::AFTER`
13. `Length`析构函数
14. `LengthTest::AFTER_CLASS`
15. `VolumeTest::BEFORE_CLASS`
16. `Volume`构造函数
17. `LengthTest::BEFORE`
18. `TEST("volume test1")`
19. `LengthTest::AFTER`
20. `Volume`析构函数
21. `Volume`构造函数
22. `LengthTest::BEFORE`
23. `TEST("volume test2")`
24. `LengthTest::AFTER`
25. `Volume`析构函数
26. `VolumeTest::AFTER_CLASS`
27. `AFTER_ALL("after all 2")`
28. `AFTER_ALL("after all 1")`


### 用例设计

#### 自动标识

cut能够自动地实现测试用例的标识功能，用户可以使用字符串来解释说明测试用例的意图，使得用户在描述用例时更加自然和方便。

```cpp
#include <cut/cut.hpp>
#include <quantity/length/Length.h>

USING_CUM_NS

FIXTURE(LengthTest)
{
    TEST("1 FEET should equal to 12 INCH")
    {
        ASSERT_THAT(Length(1, FEET), eq(Length(12, INCH)));
    }

    TEST("1 YARD should equal to 3 FEET")
    {
        ASSERT_THAT(Length(1, YARD), eq(Length(3, FEET)));
    }

    TEST("1 MILE should equal to 1760 YARD")
    {
        ASSERT_THAT(Length(1, MILE), eq(Length(1760, YARD)));
    }
};
```

#### 面向对象

cut实现xUnit时非常巧妙，使得用户设计用例时更加面向对象。`RobotCleaner robot`在每个用例执行时都将获取一个独立的、全新的实例。

```cpp
#include <cut/cut.hpp>
#include <robot-cleaner/RobotCleaner.h>
#include <robot-cleaner/Position.h>
#include <robot-cleaner/Instructions.h>

USING_CUM_NS

FIXTURE(RobotCleanerTest)
{
	RobotCleaner robot;

    TEST("at the beginning, the robot should be in at the initial position")
    {
        ASSERT_THAT(robot.getPosition(), is(Position(0, 0, NORTH)));
    }

    TEST("left instruction: 1-times")
    {
        robot.exec(left());
        ASSERT_THAT(robot.getPosition(), is(Position(0, 0, WEST)));
    }

    TEST("left instruction: 2-times")
    {
        robot.exec(left());
        robot.exec(left());
        ASSERT_THAT(robot.getPosition(), is(Position(0, 0, SOUTH)));
    }
};
```

#### 函数提取

提取的相关子函数，可以直接放在`Fixture`的内部，使得用例与其的距离最近，更加体现类作用域的概念。

```cpp
#include <cut/cut.hpp>
#include <robot-cleaner/RobotCleaner.h>
#include <robot-cleaner/Position.h>
#include <robot-cleaner/Instructions.h>

USING_CUM_NS

FIXTURE(RobotCleanerTest)
{
    RobotCleaner robot;

    void WHEN_I_send_instruction(Instruction* instruction)
    {
        robot.exec(instruction);
    }

    void AND_I_send_instruction(Instruction* instruction)
    {
        WHEN_I_send_instruction(instruction);
    }

    void THEN_the_robot_cleaner_should_be_in(const Position& position)
    {
        ASSERT_THAT(robot.getPosition(), is(position));
    }

    TEST("at the beginning")
    {
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, NORTH));
    }

    TEST("left instruction: 1-times")
    {
        WHEN_I_send_instruction(left());
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, WEST));
    }

    TEST("left instruction: 2-times")
    {
        WHEN_I_send_instruction(repeat(left(), 2));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, SOUTH));
    }

    TEST("left instruction: 3-times")
    {
        WHEN_I_send_instruction(repeat(left(), 3));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, EAST));
    }

    TEST("left instruction: 4-times")
    {
        WHEN_I_send_instruction(repeat(left(), 4));
        THEN_the_robot_cleaner_should_be_in(Position(0, 0, NORTH));
    }
};
```

### 断言

#### ASSERT_THAT

cut只支持一种断言原语：`ASSERT_THAT`, 从而避免用户在选择`ASSERT_THAT/ASSERT_NE, ASSERT_TRUE/ASSERT_FALSE`时的困扰，使其断言更加具有统一性，一致性。

此外，`ASSERT_THAT`使得断言更加具有表达力，它将实际值放在左边，期望值放在右边，更加符合英语习惯。

```cpp
#include <cut/cut.hpp>

FIXTURE(CloseToTest)
{
    TEST("close to double")
    {
        ASSERT_THAT(1.0, close_to(1.0, 0.5));
        ASSERT_THAT(0.5, close_to(1.0, 0.5));
        ASSERT_THAT(1.5, close_to(1.0, 0.5));
    }
};
```

#### Hamcrest

Hamcrest是Java社区一个轻量级的，可扩展的Matcher框架，曾被Kent Beck引入到JUnit框架中，用于增强断言的机制。cut引入了Hamcrest的设计，实现了一个C\+\+移植版本的Hamcrest，使得cutg的断言更加具有扩展性和可读性。

##### anything

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

##### 比较器

| 匹配器         | 说明            |
| ------------- |----------------|
| eq      		| 相等       		|
| ne      		| 不相等          |
| lt      		| 小于       		|
| gt      		| 大于       		|
| le      		| 小于或等于       |
| ge      		| 大于或等于       |

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

##### 修饰器

| 匹配器         | 说明            |
| ------------- |----------------|
| is      		| 可读性装饰器     |
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

#####  空指针

| 匹配器         | 说明            |
| ------------- |----------------|
| nil      		| 空指针          |

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

##### 字符串

| 匹配器           		      | 说明 				          |
| ----------------------------- |----------------------------|
| contains_string               | 断言是否包含子串  		    |
| contains_string_ignoring_case | 忽略大小写，断言是否包含子      |
| starts_with                   | 断言是否以该子串开头           |
| starts_with_ignoring_case     | 忽略大小写，断言是否以该子串开头 |
| ends_with                     | 断言是否以该子串结尾  		   |
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

##### 浮点数

| 匹配器    | 说明 				   |
| ---------|----------------------|
| close_to | 断言浮点数近似等于  	|
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

### 程序选项

```cpp
TestOptions::TestOptions() : desc("cut")
{
    desc.add({
        {"help,     h",   "help message"},
        {"filter,   f",   "--filter=pattern"},
        {"color,    c",   "--color=[yes|no]"},
        {"xml,      x",   "print test result into XML file"},
        {"list,     l",   "list all tests without running them"},
        {"progress, p",   "print test result in progress bar"},
        {"verbose,  v",   "verbosely list tests processed"},
        {"repeat,   r",   "how many times to repeat each test"}
    });
    
    // default value
    opt["color"]  = "yes";
    opt["repeat"] = "1";
}
```
