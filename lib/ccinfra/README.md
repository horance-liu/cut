# ccinfra

***

## Introduction

`ccinfra` is a `C++` infrastructure library for writting better and effective `C++` codes! It includes below main features:
- Some grammer sugar that wrappered `C++` keywords for a better cross-platform C++ programming style.
- A [DCI](https://en.wikipedia.org/wiki/Data,_context_and_interaction) programming frame for implementing composed programming in C++ easily!
- Memory utils. For example: memory allocator,  AutoMsg, TransData ...
- Data structures (eg. array, list, map) for self memory government demands! It's useful for embeded programming.
- Some algorithm for bits operator, loop, bound...
- Design pattern, such as Singleton and State pattern.
- Concurrency tools, such as thread pool, lock utils... 
- Log, an implementation of log for ccinfra.

To learn more, visit the doc folder! View the source code of tests of ccinfra in the test folder for learning how to use every library elements in details!

## Install and Test

### Get ccinfra

~~~ bash
git clone git@github.com:MagicBowen/ccinfra.git
~~~

### Build ccinfra

~~~ bash
cd ccinfra
mkdir build
cd build
cmake ..
make
~~~

### Install ccinfra

~~~ bash
sudo make install
~~~

You can also install ccinfra manually, just copy "ccinfra/include" and "ccinfra/build/src/libccinfra.a" to your special installation path.

### Test ccinfra

To test ccinfra, you need install [magellan](https://github.com/horance-liu/magellan) which is an elegant C\++ xUnit framework. Try to intall magellan by following the [magellan tutoral](https://github.com/horance-liu/magellan/blob/master/README.md)!

Following the below instructions to test ccinfra:

~~~ bash
cd build
cmake -DENABLE_TEST=1 ..
make
./test/ccinfra-test
~~~

### Supported Platform:

- [MAC OS X] supported
- [Linux] supported
- [Windows] not supported

### Supported Compilers:

- [CLANG] 3.4 or later.
- [GCC] 4.8 or later.
- [MSVC] not supported.

## Finally

Some features of ccinfra such as "sched" which based on std::thread need C\++11 suport, therefor compile all the components of ccinfra should enable the C\++11 compiling flag and link with pthread!
