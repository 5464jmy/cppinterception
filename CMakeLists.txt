cmake_minimum_required(VERSION 3.27)
project(interception)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 为 MSVC 编译器设置 UTF-8 编码支持（仅针对 C 和 CXX 编译器）
if(MSVC)
    add_compile_options("$<$<COMPILE_LANGUAGE:C>:/utf-8>")
    add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/utf-8>")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/$<CONFIG>)



file(GLOB_RECURSE SOURCES
        "${CMAKE_SOURCE_DIR}/include/*.cpp"
        "${CMAKE_SOURCE_DIR}/include/*.h"
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.h"
)
add_library(interception STATIC ${SOURCES})
target_include_directories(interception PRIVATE include)
#
#
#include_directories(
#        ${CMAKE_SOURCE_DIR}/include
#        ${CMAKE_SOURCE_DIR}/include/interception
#        ${CMAKE_SOURCE_DIR}/include/interception_c_api
#)
#
## 为 MSVC 编译器设置 UTF-8 编码支持（仅针对 C 和 CXX 编译器）
#if(MSVC)
#    add_compile_options("$<$<COMPILE_LANGUAGE:C>:/utf-8>")
#    add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/utf-8>")
#endif()

#cmake_minimum_required(VERSION 3.27)
#project(interception)
#set(CMAKE_CXX_STANDARD 20)
#
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/$<CONFIG>)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/$<CONFIG>)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/$<CONFIG>)
#
#
#file(GLOB_RECURSE SOURCES
#        "${CMAKE_SOURCE_DIR}/include/*.cpp"
#        "${CMAKE_SOURCE_DIR}/include/*.h"
#        "${CMAKE_SOURCE_DIR}/src/*.cpp"
#        "${CMAKE_SOURCE_DIR}/src/*.h"
#)
#add_library(interception STATIC ${SOURCES})
#target_include_directories(interception PRIVATE include)