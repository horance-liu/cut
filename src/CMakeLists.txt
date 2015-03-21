FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

sort_files(all_files)

add_library(magellan STATIC ${all_files})
install(TARGETS magellan ARCHIVE DESTINATION lib)
