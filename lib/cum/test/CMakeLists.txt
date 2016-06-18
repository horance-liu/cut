project(cum-test)

include_directories(${cut_INCLUDE_DIR})

FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_executable(cum-test ${all_files})
target_link_libraries(cum-test cum options cut cub)
