FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_library(hamcrest STATIC ${all_files})
install(TARGETS hamcrest ARCHIVE DESTINATION lib)
