cmake_minimum_required(VERSION 3.25)
project(largeintcalculator C)

set(CMAKE_C_STANDARD 17)

if(WIN32)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/builds/Windows/${CMAKE_BUILD_TYPE})
elseif(APPLE)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/builds/macOS/${CMAKE_BUILD_TYPE})
else()
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/builds/Linux/${CMAKE_BUILD_TYPE})
endif()

add_executable(largeintcalculator largeintcalculator.c)
