# Magellan: A Simple xUnit Test Framework in Modern C++11

## 你无法忍受Google Test的9个特性

### 用例描述必须遵循严格的标识符规则

这种严格的规则，虽然给Google Test的实现带来了诸多便捷之处，但这给用户造成了很大的负担。尤其当一个用例需要描述一个数学逻辑规则时，用例的表达力将大大折扣。

```cpp
TEST_F(RobotCleanerTest, at_the_beginning_the_robot_should_be_in_at_the_initial_position)
{
    ASSERT_EQ(Position(0, 0, NORTH), robot.getPosition());
}
```

### 贯穿着“重复设计”的坏味道

如下例，每个`TEST_F`用例都要重复一次`RobotCleanerTest`。

```cpp
struct RobotCleanerTest : testing::Test
{
protected:
    RobotCleaner robot;
};

TEST_F(RobotCleanerTest, at_the_beginning_the_robot_should_be_in_at_the_initial_position)
{
    ASSERT_EQ(Position(0, 0, NORTH), robot.getPosition());
}

TEST_F(RobotCleanerTest, should_be_face_west_after_turn_left)
{
   robot.turnLeft();
   ASSERT_EQ(Position(0, 0, WEST), robot.getPosition());
}
```

### Fixture与TEST_F存在隐晦的继承关系

这也是上例中将`RobotCleaner robot`声明为`protected`的原因。这种隐晦的继承关系，让刚刚入门使用Google Test的人都大吃一惊。

当然，如果你了解过Google Test的实现技术(`TEST_F`展开后将生成`Fixture`的一个子类，并自动地注册到框架中)，或者已经习惯了他的的设计，这自然不是问题。


### TEST， TEST_F的设计容易让人误解、误用

`TEST_F`的第一个参数是`Fixture`的名字。如下例如果被误用为`TEST`，最理想的情况下，则发生编译时错误。如本例所示，编译器将提示`robot`是一个未定义的变量。最坏的情况下是，错误发生在运行时，可能存在没有调用预期的`SetUp/TearDown`的风险。

```cpp
struct RobotCleanerTest : testing::Test
{
protected:
    RobotCleaner robot;
};

TEST_F(RobotCleanerTest, at_the_beginning_the_robot_should_be_in_at_the_initial_position)
{
    ASSERT_EQ(Position(0, 0, NORTH), robot.getPosition());
}
```

### 重写SetUp/TearDown时，缺乏Override的保护

Google Test通过在子类中改写`Setup/TearDown`来定制`Fixture`的功能，但程序员往往易于混淆`setUp, Setup, SetUp, set_up`，尤其在C\+\+98中，由于缺失`override`的编译时保护，易于让程序员写出违背原意的逻辑代码，这样的错误很可能是运行时错误。

```cpp
struct RobotCleanerTest : testing::Test
{
    virtual void Setup()   // 本应该为SetUp
    {
        robot.reset();
    }

protected:
    RobotCleaner robot;
};
```

### 不符合OO的习惯

每个`TEST_F/TEST`的实现，感觉是一个个游离的函数，是一个典型的过程式设计，通过重复地使用`RobotCleanerTest`而使它们联系在一起，这太过于牵强。

此外，需要提取函数时，要么将函数提取到父类的`Fixture`中，要么提取到匿名的`namespace`中，物理上隔离非常远，尤其用例数目很多的时候，问题更突出。无论怎么样，Google Test缺乏严格意义上的OO设计。

```cpp
struct RobotCleanerTest : testing::Test
{

protected:
    RobotCleaner robot;
};

TEST_F(RobotCleanerTest, at_the_beginning_the_robot_should_be_in_at_the_initial_position)
{
    ASSERT_EQ(Position(0, 0, NORTH), robot.getPosition());
}

TEST_F(RobotCleanerTest, should_be_face_west_after_turn_left_1_times)
{
    robot.turnLeft();
    ASSERT_EQ(Position(0, 0, WEST), robot.getPosition());
}

TEST_F(RobotCleanerTest, should_be_face_south_after_turn_left_2_times)
{
    robot.turnLeft();
    robot.turnLeft();
    ASSERT_EQ(Position(0, 0, SOUTH), robot.getPosition());
}

TEST_F(RobotCleanerTest, should_be_face_east_after_turn_left_3_times)
{
    robot.turnLeft();
    robot.turnLeft();
    robot.turnLeft();
    ASSERT_EQ(Position(0, 0, EAST), robot.getPosition());
}

TEST_F(RobotCleanerTest, should_be_face_north_after_turn_left_4_times)
{
    robot.turnLeft();
    robot.turnLeft();
    robot.turnLeft();
    robot.turnLeft();
    ASSERT_EQ(Position(0, 0, NORTH), robot.getPosition());
}
```

### 断言违背直觉

把期望值放在前面，而把实际值放在后面，严重违反了英语的阅读习惯。犹如我讨厌诸如`if (NULL != ptr)`的反人类的代码一样。

```cpp
ASSERT_EQ(Position(0, 0, WEST), robot.getPosition());
```

### Global级Fixture不能自动发现

`GlobalEnvironment`需要手动注册到框架，才能被框架发现，而不像`TEST_F, TEST, TEST_G`无需显式地注册，便能被框架自动发现，设计缺乏统一性，一致性。

```cpp
#include "gtest/gtest.h"

struct GlobalEnvironment : testing::Environment
{
    virtual void SetUp()
    { ... }

    virtual void TearDown()
    { ... }
};

int main(int argc, char** argv)
{
    testing::AddGlobalTestEnvironment(new GlobalEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

### 断言缺乏可扩展性

使用Google Test的断言时，你可以在`ASSERT_EQ, ASSERT_NE, ASSERT_TRUE, ASSERT_FALSE`之中做选择。当然你可以认为这无可厚非，但这样的设计最大的问题在于：只能使用框架本身所提供的几个为数不多的断言原语，缺乏可扩展性，或者扩展起来非常困难。

例如你想增加个一个`ASSERT_NIL`的断言，扩展起来变得非常不自然。

### 没有理由，就是不喜欢

在C\+\+社区中，有很多人在使用Google Test。这归功于它在平台性移植、部署与安装等方面非常成功，尤其符合微软平台上的C++程序员的胃口；其次，Google Test的`TEST, TEST_F`实现的自动发现机制，相对于CppUnit等框架显得更技高一筹。

但对于高级别的、骨灰级的C++程序员，是无法容忍上述的Google Test的致命性缺陷的，例如严格的标识符命名规则，这种强制的约束几乎等于杀了他。

## Magellan：开启新的征程

### 灵感

Magellan是一个简单的、可扩展的、使用C\+\+11实现的xUnit测试框架。Magellan设计灵感来自于Java社区著名的测试框架JUnit。

### 安装

#### Gitlab

地址：[https://gitlab.com/horance/magellan](https://gitlab.com/horance/magellan)
作者：刘光聪
Email：[horance@outlook.com](horance@outlook.com)

#### 编译环境

支持的平台:
* [MAC OS X] supported
* [Linux] supported
* [Windows] not supported

支持的编译器:
* [CLANG] 3.4 or later.
* [GCC] 4.8 or later.
* [MSVC] not supported.

#### 安装CMake

CMake的下载地址：[http://www.cmake.org](http://www.cmake.org)。

#### 安装l0-infra

Magellan依赖于l0-infra，所以必须先安装l0-infra。

```bash
$ git clone https://gitlab.com/horance/l0-infra.git
$ cd l0-infra
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

#### 安装Magellan

```bash
$ git clone https://gitlab.com/horance/magellan.git
$ cd magellan
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
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
#include "magellan/magellan.hpp"


int main(int argc, char** argv)
{
    return magellan::run_all_tests(argc, argv);
}
```

##### CMakeList脚本

```cmake
project(quantity)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE all_files
src/*.cpp
src/*.cc
src/*.c
test/*.cpp
test/*.cc
test/*.c)

add_executable(quantity-test ${all_files})

target_link_libraries(quantity-test magellan l0-infra)
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

[==========] Running 0 test cases.
[----------] 0 tests from All Tests
[----------] 0 tests from All Tests

[==========] 0 test cases ran.
[  TOTAL   ] PASS: 0  FAILURE: 0  ERROR: 0  TIME: 0 us
```

### 体验Magellan

#### 第一个用例

```cpp
#include <magellan/magellan.hpp>

#include "quantity/Length.h"

USING_HAMCREST_NS

FIXTURE(LengthTest)
{
    TEST("1 FEET should equal to 12 INCH")
    {
        ASSERT_THAT(Length(1, FEET), eq(Length(12, INCH)));
    }
};
```

使用 Magellan,只需要包含 `magellan.hpp` 一个头文件即可。Magellan 使用 Hamcrest 的断言机制,
使得断言更加统一、自然,且具有良好的扩展性;使用 `USING_HAMCREST_NS`,从而可以使用 `eq` 代
替 `hamcrest::eq`,简短明确;除非出现名字冲突,否则推荐使用简写的 `eq`。

#### Length实现

```cpp
// quantity/Length.h
#include "quantity/Amount.h"

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
#include "quantity/Length.h"

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
#include <magellan/magellan.hpp>

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
#include <magellan/magellan.hpp>

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

有时候需要在所有用例启动之前完成一次性的全局性的配置，在所有用例运行完成之后完成一次性的清理工作。Magellan则使用`BEFORE_ALL`和`AFTER_ALL`两个关键字来支持这样的特性。

```cpp
#include <magellan/magellan.hpp>

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

`BEFORE_ALL`和`AFTER_ALL`向系统注册`Hook`即可，Magellan便能自动地发现它们，并执行它们。犹如C\+\+不能保证各源文件中全局变量初始化的顺序一样，避免在源文件之间的`BEFORE_ALL`和`AFTER_ALL`设计不合理的依赖关系。

```cpp
#include <magellan/magellan.hpp>

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
#include <magellan/magellan.hpp>

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

Magellan可能的一个执行序列为：

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

Magellan能够自动地实现测试用例的标识功能，用户可以使用字符串来解释说明测试用例的意图，使得用户在描述用例时更加自然和方便。

```cpp
#include <magellan/magellan.hpp>
#include "quantity/length/Length.h"

USING_HAMCREST_NS

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

Magellan实现xUnit时非常巧妙，使得用户设计用例时更加面向对象。`RobotCleaner robot`在每个用例执行时都将获取一个独立的、全新的实例。

```cpp
#include "magellan/magellan.hpp"
#include "robot-cleaner/RobotCleaner.h"
#include "robot-cleaner/Position.h"
#include "robot-cleaner/Instructions.h"

USING_HAMCREST_NS

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
#include "magellan/magellan.hpp"
#include "robot-cleaner/RobotCleaner.h"
#include "robot-cleaner/Position.h"
#include "robot-cleaner/Instructions.h"

USING_HAMCREST_NS

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

Magellan只支持一种断言原语：`ASSERT_THAT`, 从而避免用户在选择`ASSERT_EQ/ASSERT_NE, ASSERT_TRUE/ASSERT_FALSE`时的困扰，使其断言更加具有统一性，一致性。

此外，`ASSERT_THAT`使得断言更加具有表达力，它将实际值放在左边，期望值放在右边，更加符合英语习惯。

```cpp
#include <magellan/magellan.hpp>

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

Hamcrest是Java社区一个轻量级的，可扩展的Matcher框架，曾被Kent Beck引入到JUnit框架中，用于增强断言的机制。Magellan引入了Hamcrest的设计，实现了一个C\+\+移植版本的Hamcrest，使得Magellang的断言更加具有扩展性和可读性。

##### anything

| 匹配器         | 说明           |
| ------------- |---------------|
| anything      | 总是匹配       |
| _             | anything语法糖 |

```cpp
#include <magellan/magellan.hpp>

USING_HAMCREST_NS

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
#include <magellan/magellan.hpp>

USING_HAMCREST_NS

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
#include <magellan/magellan.hpp>

USING_HAMCREST_NS

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
#include <magellan/magellan.hpp>

USING_HAMCREST_NS

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
#include <magellan/magellan.hpp>

USING_HAMCREST_NS

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
#include <magellan/magellan.hpp>
#include <math.h>

USING_HAMCREST_NS

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
TestOptions::TestOptions() : desc("magellan")
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
    options["color"]  = "yes";
    options["repeat"] = "1";
}
```
