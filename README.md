# Mangellan: A Simple xUnit Test Framework in Modern C++11

[cut](http://gitlab.com/horance/cut) is a simple, practical, and scalable xUnit Test Framework in Modern C++11. It's inspiration comes from the famous testing framework JUnit in Java community.

C/C++ are different languages from most modern ones. Writing tests for them has some very specific challenges. Therefore, simply clone ideas from xUnit frameworks for other languages does not work the best. Programmers have to suffer accidental complexities brought by most of existing frameworks.

**cut** is designed for simplifying efforts of programers, in terms of development, maintenance, flexibility of test management, build & run-time strategy, and others.

Supported Platform:
* [MAC OS X] supported
* [Linux] supported
* [Windows] not supported

Supported Compilers:
* [CLANG] 3.4 or later.
* [GCC] 4.8 or later.
* [MSVC] not supported.

Dependences:
* [cub](git clone https://github.com/ccup/cub.git).
* [opt](git clone https://github.com/ccup/opt.git).
* [cum](https://github.com/horance-liu/cum).

## Installing

### Clone cut

```bash
$ git clone https://github.com:ccup/cut.git
```

### Install Dependencies

```bash
$ cd cut/lib
$ git clone https://github.com/ccup/cub.git
$ cd cub && mkdir build && cd build
$ cmake .. && make
$ sudo make install 
```

### Install cut

First, Install `cum`：

```bash
$ cd cut/lib/cum && mkdir build && cd build
$ cmake .. && make
$ sudo make install 
```

Second, Intall `opt`：

```bash
$ cd cut/lib/opt && mkdir build && cd build
$ cmake .. && make
$ sudo make install 
```

At last, Install `cut`：

```bash
$ cd cut && mkdir build && cd build
$ cmake .. && make
$ sudo make install 
```

##### Test cut

```bash
$ cd cut/build
$ cmake -DENABLE_TEST=on .. && make
$ test/cut-test
```

### Using Rake

```bash
$ rake deps      # install all dependencies
```

Run commands if using GCC:

```bash
$ rake clone         # clone all dependencies
$ rake build[gcc]    # clone all dependencies
```

Other tasks:

```bash
$ rake             # build, install cut using clang
$ rake build       # build, install using clang
$ rake test        # build, install, and test using clang
$ rake build[gcc]  # build, install using gcc
$ rake test[gcc]   # build, install, and test using gcc
$ rake uninstall   # uninstall cut only
$ rake clean       # remove temp directory, and uninstall cut
```

And other task for dependencies:

```bash
$ rake deps             # clone, build, install all dependencies using clang
$ rake deps_clone       # clone all dependencies
$ rake deps_build       # clone, build, install all dependencies using clang
$ rake deps_test        # clone, build, install, and test all dependencies using clang
$ rake deps_build[gcc]  # clone, build, install all dependencies using gcc
$ rake deps_test[gcc]   # clone, build, install, and test all dependencies using gcc
$ rake deps_uninstall   # uninstall all dependencies
$ rake deps_clean       # remove temp directory, and uninstall all dependencies
```

## Begin the new journey

### Ice Breaking

##### Physical Directory

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

##### main

```cpp
#include <cut/cut.hpp>


int main(int argc, char** argv)
{
    return cut::run_all_tests(argc, argv);
}
```

##### CMakeList

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

target_link_libraries(quantity-test cut cum cub)
```

- cut: C++ Unified Test framework;
- cum: C++ Universal Matchers;
- opt: C++ Program Options;
- cub: C++ Unified Base Libary;

##### Build

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

##### Run Test

```bash
$ ./quantity-test

[==========] Running 0 test cases.
[----------] 0 tests from All Tests
[----------] 0 tests from All Tests

[==========] 0 test cases ran.
[  TOTAL   ] PASS: 0  FAILURE: 0  ERROR: 0  TIME: 0 us
```

### cut Experience

#### First Test Case

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

#### Length Implements

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

##### Build

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

##### Run Test

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

Test fixture can be divided into three categories: 

* Independent Fixture
* Shared Fixture 
* Global Fixture.

#### BDD Style

| xUnit         | BDD           |
| ------------- |---------------|
| FIXTURE       | CONTEXT       |
| SETUP         | BEFORE        |
| TEARDOWN      | AFTER         |
| ASSERT_THAT   | EXPECT        |

#### Independent Fixture

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

Executing sequence：
1. `Length` Constructor
2. `SETUP`
3. `TEST("length test1")`
4. `TEARDOWN`
5. `Length` Destructor
6. `Length` Constructor
7. `SETUP`
8. `TEST("length test2")`
9. `TEARDOWN`
10. `Length` Destructor

#### Shared Fixture

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

Executing squence：
1. `BEFORE_CLASS`
2. `Length` Constructor
3. `BEFORE`
4. `TEST("length test1")`
5. `AFTER`
6. `Length` Destructor
7. `Length` Constructor
8. `BEFORE`
9. `TEST("length test2")`
10. `AFTER`
11. `Length` Destructor
12. `AFTER_CLASS`

#### Global Fixture

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

Possible executing squence：

1. `BEFORE_ALL("before all 1")`
2. `BEFORE_ALL("before all 2")`
3. `LengthTest::BEFORE_CLASS`
4. `Length` Constructor
5. `LengthTest::BEFORE`
6. `TEST("length test1")`
7. `LengthTest::AFTER`
8. `Length` Destructor
9. `Length` Constructor
10. `LengthTest::BEFORE`
11. `TEST("length test2")`
12. `LengthTest::AFTER`
13. `Length` Destructor
14. `LengthTest::AFTER_CLASS`
15. `VolumeTest::BEFORE_CLASS`
16. `Volume` Constructor
17. `LengthTest::BEFORE`
18. `TEST("volume test1")`
19. `LengthTest::AFTER`
20. `Volume` Destructor
21. `Volume` Constructor
22. `LengthTest::BEFORE`
23. `TEST("volume test2")`
24. `LengthTest::AFTER`
25. `Volume` Destructor
26. `VolumeTest::AFTER_CLASS`
27. `AFTER_ALL("after all 2")`
28. `AFTER_ALL("after all 1")`


### Case Design 

#### Auto Identification

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

#### OO

A independant and new instance `RobotCleaner robot` will be created for each test case.

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

#### Extract Method

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

### Assertion

#### ASSERT_THAT

`ASSERT_THAT` makes assertions more expressive, it will be the actual value on the left, but the desired value on the right, and more consistent with English habits.

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

Hamcrest is a lightweight, extensible matcher framework that has been introduced into the JUnit framework by Beck Kent. cut introduces the design of Hamcrest, implements a C\+\+ porting version of Hamcrest, which makes the assertion of cutg more scalable and readable.

##### anything

| Matcher       | Description               |
| ------------- |---------------------------|
| anything      | always matched            |
| _             | syntax sugar of anything  |

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

##### Comparator

| Matcher       | Description         |
| ------------- |---------------------|
| eq            | equal to            |
| ne            | not equal to        |
| lt            | less than           |
| gt            | greater than        |
| le            | less or equal to    |
| ge            | greater or equal to |

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

##### Decorator

| Matcher       | Description         |
| ------------- |----------------|
| is            | is decorator   |
| is_not        | not decorator  |

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

#####  NULL Pointer

| Matcher       | Description         |
| ------------- |----------------|
| nil           | null pointer   |

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

##### String

| Matcher                       | Description                            |
| ----------------------------- |----------------------------------------|
| contains_string               | contains a sub-string                  |
| contains_string_ignoring_case | contains a sub-string ignoring case    |
| starts_with                   | starts with a sub-string               |
| starts_with_ignoring_case     | starts with a sub-string ignoring case |
| ends_with                     | ends with a sub-string                 |
| ends_with_ignoring_case       | ends with a sub-string ignoring case   |

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

##### Float

| Matcher  | Description             |
| ---------|-------------------------|
| close_to | close to a float number |
| nan      | not a number            |

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

### cut Options

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

## Copyright
Copyright (c) 2015-2020 Horance Liu. See LICENSE for details.
