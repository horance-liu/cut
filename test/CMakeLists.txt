project(magellan-test)

include_directories(${MAGELLAN_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../test)

FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

sort_files(all_files)

add_executable(magellan-test  ${all_files})
target_link_libraries(magellan-test ${MAGELLAN_LIBRARIES} hamcrest)
