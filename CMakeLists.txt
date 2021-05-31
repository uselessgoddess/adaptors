cmake_minimum_required(VERSION 3.19)
project(adaptors)
include(help.cmake)

add_library(adaptors INTERFACE)
    target_include_directories(adaptors INTERFACE src)
    set_target_properties(adaptors PROPERTIES CXX_STANDARD 20)

subdirectories_list(SUBDIR_LIST_ADAPTORS ${CMAKE_CURRENT_LIST_DIR}/examples/adaptors)
subdirectories_list(SUBDIR_LIST_CURRY ${CMAKE_CURRENT_LIST_DIR}/examples/curry)

foreach(DIR ${SUBDIR_LIST_ADAPTORS})
    set(EXECUTABLE adaptors.${DIR})
    add_executable(${EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/examples/adaptors/${DIR}/main.cpp)
    set_target_properties(${EXECUTABLE} PROPERTIES CXX_STANDARD 20)
    target_link_libraries(${EXECUTABLE} PUBLIC adaptors)
endforeach()

foreach(DIR ${SUBDIR_LIST_CURRY})
    set(EXECUTABLE curry.${DIR})
    add_executable(${EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/examples/curry/${DIR}/main.cpp)
    set_target_properties(${EXECUTABLE} PROPERTIES CXX_STANDARD 20)
    target_link_libraries(${EXECUTABLE} PUBLIC adaptors)
endforeach()
