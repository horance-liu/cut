file(GLOB_RECURSE main_src
  "main.cpp"
)

FILE(GLOB_RECURSE cub_srcs
*.cpp
*.cc
*.c++
*.c
*.C)
list(REMOVE_ITEM cub_srcs ${main_src})

add_library(cut STATIC ${cub_srcs})
install(TARGETS cut ARCHIVE DESTINATION lib)

add_library(cut-main STATIC ${main_src})
install(TARGETS cut-main ARCHIVE DESTINATION lib)
