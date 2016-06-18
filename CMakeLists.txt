project(cut)

cmake_minimum_required(VERSION 2.8)

set(ENABLE_TEST OFF CACHE BOOL "Enable the test")

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -g -std=c++11")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(src)

if(ENABLE_TEST)
    add_subdirectory(test)
endif()

install(DIRECTORY include/cut DESTINATION include)
