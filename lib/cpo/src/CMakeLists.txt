FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_library(cpo STATIC ${all_files})

install(TARGETS cpo ARCHIVE DESTINATION lib)

