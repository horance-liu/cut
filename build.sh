#!/bin/bash

working_path=$PWD

echo "try build ${working_path}"
echo "*******************************************************************************"
echo "start generate cmake eclipse project..."

if [ ! -d "build" ]; then
    mkdir -p build
fi

cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# execute cmake when you using colorgcc
# CC="colorgcc /usr/bin/gcc" CXX="colorgcc /usr/bin/g++" cmake -DCMAKE_BUILD_TYPE=Debug ..

# execute cmake when you using distcc
# export DISTCC_HOSTS="localhost 10.93.114.73"
# CC="distcc /usr/bin/gcc" CXX="distcc /usr/bin/g++" cmake -DCMAKE_BUILD_TYPE=Debug ..

echo "*******************************************************************************"
echo "start build cmake project..."

make -j4

if [ $? -ne 0 ]; then
    echo "build ${working_path} fail"
    exit 1
fi

echo "*******************************************************************************"
echo "start run tests..."

test/magellan-test --gtest_color=yes $1 $2
examples/robot-cleaner/robot-cleaner-test --gtest_color=yes $1 $2

if [ $? -ne 0 ]; then
    echo "build ${working_path} fail"
    exit 1
fi

cd ..

echo "*******************************************************************************"
echo "build ${working_path} succ"

