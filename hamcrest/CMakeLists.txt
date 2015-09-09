add_subdirectory(src)

if(ENABLE_TEST)
  add_subdirectory(test)
endif()

install(DIRECTORY include/hamcrest DESTINATION include)