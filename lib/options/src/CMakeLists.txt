FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_library(options STATIC ${all_files})

install(TARGETS options ARCHIVE DESTINATION lib)

