project(hamcrest-test)

include_directories(${MAGELLAN_INCLUDE_DIR})

FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_executable(hamcrest-test ${all_files})
target_link_libraries(hamcrest-test hamcrest magellan ccinfra)
