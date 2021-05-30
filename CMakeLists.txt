cmake_minimum_required(VERSION 3.19)
project(adaptors)
include(help.cmake)

add_library(adaptors INTERFACE)
    target_include_directories(adaptors INTERFACE src)
    set_target_properties(adaptors PROPERTIES CXX_STANDARD 20)

subdirectories_list(SUBDIR_LIST ${CMAKE_CURRENT_LIST_DIR}/examples)

foreach(DIR ${SUBDIR_LIST})
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/examples/${DIR})
    set_target_properties(${DIR} PROPERTIES CXX_STANDARD 20)
    target_link_libraries(${DIR} PUBLIC adaptors)
endforeach()
