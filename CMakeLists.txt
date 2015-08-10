project(magellan)

cmake_minimum_required(VERSION 2.8)

set(ENABLE_TEST OFF CACHE BOOL "Enable the test")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

set(MAGELLAN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${MAGELLAN_INCLUDE_DIR})
install(DIRECTORY include/hamcrest include/magellan DESTINATION include)

add_subdirectory(src)

if(ENABLE_TEST)
  add_subdirectory(test)
endif()
