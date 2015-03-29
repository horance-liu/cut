#!/bin/bash

# execute cmake when you using colorgcc
# CC="colorgcc /usr/bin/gcc" CXX="colorgcc /usr/bin/g++" cmake -DCMAKE_BUILD_TYPE=Debug ..

# execute cmake when you using distcc
# export DISTCC_HOSTS="localhost 10.93.114.73"
# CC="distcc /usr/bin/gcc" CXX="distcc /usr/bin/g++" cmake -DCMAKE_BUILD_TYPE=Debug ..

# working_path=$PWD

function start_exec()
{
  echo -e "\033[0;35;1m*******************************************************************************************************\033[0m"
  echo -e "\033[0;35;1mstart to $1 \033[0m"
}

function exec_on_fail()
{
  start_exec "run $1"

  $1
  
  if [ $? -ne 0 ]; then
    echo "build $1 fail"
    exit 1
  fi
}
 
#export CC=/usr/bin/clang
#export CXX=/usr/bin/clang++

start_exec "generate makefile"
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DMAGELLAN_ENABLE_TEST=ON ..

start_exec "make"
exec_on_fail make 

function run_test()
{
  exec_on_fail "test/$1/$1-test $2 --gtest_color=yes"
}

run_test quantity --gtest_filter=*.*
run_test robot-cleaner --gtest_filter=*.*
run_test magellan --gtest_filter=*.*

cd ..
