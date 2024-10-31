cmake_minimum_required(VERSION 3.28)
project(interception)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib/$<CONFIG>)

add_library(interception STATIC
        include/interception/interception.h
        include/interception/listener.h
        include/interception/input.h
        include/interception/core.h
        include/interception/beziercurve.h
        include/interception/exceptions.h
        src/interception_c_api/interception.cpp
        src/interception_c_api/interception.h
        src/input.cpp
        src/keyboard.cpp
        src/keyboard.h
        src/mouse.cpp
        src/mouse.h
        src/exceptions.cpp
        src/beziercurve.cpp
        src/listener.cpp
        src/context.cpp
        src/context.h
)

target_include_directories(interception PRIVATE include)