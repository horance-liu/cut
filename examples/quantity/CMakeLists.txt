project(quantity)

include_directories(${MAGELLAN_INCLUDE_DIR} include)

FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

sort_files(all_files)

add_executable(quantity-test ${all_files} ../main.cpp)
target_link_libraries(quantity-test magellan infra hamcrest)
