cmake_minimum_required(VERSION 2.8)

project(magellan)

set(ENABLE_TEST OFF CACHE BOOL "Enable the test")

#
# File Filter
#

MACRO(sort_files source_files)
  SET(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
  FOREACH(sgbd_file ${${source_files}})
    STRING(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
    STRING(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
    STRING(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
    IF(MSVC)
      string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
    ENDIF(MSVC)
    IF(sgbd_nogroup)
      SET(sgbd_group_name "\\")
    ENDIF(sgbd_nogroup)
    SOURCE_GROUP(${sgbd_group_name} FILES ${sgbd_file})
  ENDFOREACH(sgbd_file)
ENDMACRO(sort_files)

#
# Generic Compiler Flags
#

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /vmg")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX")
endif()

#
# Magellan
#

set(MAGELLAN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${MAGELLAN_INCLUDE_DIR})

set(MAGELLAN_LIBRARIES magellan stdc++)

install(DIRECTORY include/hamcrest include/magellan DESTINATION include)

add_subdirectory(src)

if(ENABLE_TEST)
  add_subdirectory(test)
endif()

