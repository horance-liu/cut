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

Dependces:
* [Infrastructure](https://gitloab.com/horance/infrastructure).
* [Hamcrest](https://gitlab.com/horance/hamcrest).

## Installation

### Update GCC to 4.9

In order to support full C++11/14 features, to update GCC to 4.9 or later.

    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get install gcc-4.9 g++-4.9
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9
    sudo update-alternatives --config gcc

### Install CMake:

    sudo apt-get install cmake
  
### Install Infrastructure: 
  
    git clone https://gitlab.com/horance/infrastructure.git
    cd infrastructure
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

### Install Hamcrest: 
    
    git clone https://gitlab.com/horance/hamcrest.git
    cd hamcrest 
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

### Install Magellan:

    mkdir build
    cd build
    cmake ..
    make
    sudo make install

### NOTE

You can run build.sh only if infrastructure and hamcrest installed.

## Copyright
Copyright (c) 2015-2020 Horance Liu. See LICENSE for details.
