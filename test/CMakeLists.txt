project(cut-test)

include_directories(${cut_INCLUDE_DIR} robot-cleaner/include quantity/include)

FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_executable(cut-test ${all_files})
target_link_libraries(cut-test cut_main cut)
