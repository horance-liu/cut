project(magellan)

cmake_minimum_required(VERSION 2.8)

set(ENABLE_TEST OFF CACHE BOOL "Enable the test")

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

set(MAGELLAN_INCLUDE_DIR 
${CMAKE_CURRENT_SOURCE_DIR}/lib/l0-infra/include
${CMAKE_CURRENT_SOURCE_DIR}/lib/hamcrest/include
${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${MAGELLAN_INCLUDE_DIR})

add_subdirectory(lib/l0-infra)
add_subdirectory(lib/hamcrest)
add_subdirectory(src)

if(ENABLE_TEST)
    add_subdirectory(test)
endif()

install(DIRECTORY include/magellan DESTINATION include)
