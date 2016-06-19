project(cpo-test)

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

add_executable(cpo-test ${all_files})
target_link_libraries(cpo-test cut cum cpo cub)
