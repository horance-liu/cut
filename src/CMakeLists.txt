FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_library(cut STATIC ${all_files})
install(TARGETS cut ARCHIVE DESTINATION lib)
