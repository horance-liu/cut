FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_library(opt STATIC ${all_files})

install(TARGETS opt ARCHIVE DESTINATION lib)

