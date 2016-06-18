FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_library(ccinfra STATIC ${all_files})

install(TARGETS ccinfra ARCHIVE DESTINATION lib)

