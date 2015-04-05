# Mangellan

[Magellan](http://gitlab.com/horance/magellan) is a simple implement for xUnit framework using C++11/14.

Supported Platform:
* [MAC OS X] supported
* [Linux] supported
* [Windows] not supported

Supported Compilers:
* [CLANG] 3.5 or later.
* [GCC] 4.9 or later.
* [MSVC] not supported.

Dependences:
* [l0-infra](https://gitloab.com/horance/l0-infra).

## Installation

### Update GCC to 4.9

In order to support full C++11/14 features, to update GCC to 4.9 or later.

    sudo -E add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get install gcc-4.9 g++-4.9
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9
    sudo update-alternatives --config gcc

### Install CMake:

    sudo apt-get install cmake
  
### Install l0-infra: 
  
    git clone https://gitlab.com/horance/l0-infra.git
    cd l0-infra
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
    sudo ldconfig

### Install Magellan:

    mkdir build
    cd build
    cmake ..
    make
    sudo make install
    sudo ldconfig

### Test Magellan
  
    cd build
    cmake -DENABLE_TEST=on ..
    make
    test/magellan-test

### Magellan Developer

TO see [magellan-dev-kit](https://gitloab.com/horance/magellan-dev-kit) README for details.

## Copyright
Copyright (c) 2015-2020 Horance Liu. See LICENSE for details.
