# Mangellan

[Magellan](http://gitlab.com/horance/magellan) is a simple implement for xUnit framework in modern C++11.

Supported Platform:
* [MAC OS X] supported
* [Linux] supported
* [Windows] not supported

Supported Compilers:
* [CLANG] 3.4 or later.
* [GCC] 4.8 or later.
* [MSVC] not supported.

Dependences:
* [l0-infra](https://gitloab.com/horance/l0-infra).

## Installation

### Install CMake:

```bash
$ sudo apt-get install cmake
```
  
### Install l0-infra: 

```bash  
$ git clone https://gitlab.com/horance/l0-infra.git
$ cd l0-infra
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
$ sudo ldconfig
```

### Install Magellan:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
$ sudo ldconfig
```

### Test Magellan
  
```bash
$ cd build
$ cmake -DENABLE_TEST=on ..
$ make
$ test/magellan-test
```

### Magellan Developer

TO see [MDK](https://gitloab.com/horance/mdk) README.md for details.

## Copyright
Copyright (c) 2015-2020 Horance Liu. See LICENSE for details.
