file(GLOB_RECURSE main_src
  "main.cpp"
)

FILE(GLOB_RECURSE cut_srcs
*.cpp
*.cc
*.c++
*.c
*.C)
list(REMOVE_ITEM cut_srcs ${main_src})

add_library(cut STATIC ${cut_srcs})
install(TARGETS cut ARCHIVE DESTINATION lib)

add_library(cut_main STATIC ${main_src})
install(TARGETS cut_main ARCHIVE DESTINATION lib)
