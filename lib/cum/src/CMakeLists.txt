FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_library(cum STATIC ${all_files})
install(TARGETS cum ARCHIVE DESTINATION lib)
