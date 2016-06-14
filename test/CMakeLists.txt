project(magellan-test)

include_directories(${MAGELLAN_INCLUDE_DIR} robot-cleaner/include quantity/include)

FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_executable(magellan-test ${all_files})
target_link_libraries(magellan-test magellan hamcrest ccinfra)
