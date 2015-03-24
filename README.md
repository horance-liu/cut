# Mangellan

Mangellan is a simple implement for xUnit framework using C++11/14.

* [Magellan Website](http://gitlab.com/horance/magellan)

Supported Platform:
* [MAC OS X] supported
* [Linux] supported
* [Windows] not supported

Supported Compilers:
* [CLANG] 3.5 or later.
* [GCC] 4.9 or later.
* [MSVC] not supported.

Dependces:
* [Google Test](http://code.google.com/p/googletest/) 1.6 or later.

## Installation

### Update GCC to 4.9

In order to support full C++11/14 features, to update GCC to 4.9 or later.

    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt-get update
    sudo apt-get install gcc-4.9 g++-4.9
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9
    sudo update-alternatives --config gcc

### Install dependces:

#### Install CMake:

    sudo apt-get install cmake
  
#### Install Google Test dependces:

    sudo apt-get install google-mock
    cd /usr/src/gmock/gtest
    sudo mkdir build
    cd build
    sudo cmake ..
    sudo make
    sudo mv libg* /usr/local/lib/ 
    cd ..
    sudo cp -aR include/gtest/ /usr/local/include/
    sudo ldconfig

### Build and Install Magellan:

    mkdir build
    cd build
    cmake ..
    make
    sudo make install

## Copyright
Copyright (c) 2015-2020 Horance Liu. See LICENSE for details.
