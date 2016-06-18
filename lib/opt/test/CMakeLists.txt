project(opt-test)

include_directories(${cut_INCLUDE_DIR})

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_executable(opt-test ${all_files})
target_link_libraries(opt-test cum opt cut cub)
